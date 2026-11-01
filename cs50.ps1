# Open a CS50 Linux terminal, or run a command in this workspace's container.
# Examples: .\cs50.ps1 ; .\cs50.ps1 check50 --version
param([Parameter(ValueFromRemainingArguments = $true)][string[]]$Command)

$ErrorActionPreference = 'Stop'
$workspacePath = $PSScriptRoot

& docker info --format '{{.OSType}}' *> $null
if ($LASTEXITCODE -ne 0) { throw 'Start Docker Desktop first, then run this script again.' }

$candidateIds = @(& docker ps -aq --filter 'label=devcontainer.local_folder')
$containerId = $null
if ($candidateIds.Count -gt 0) {
    $containers = (& docker inspect @candidateIds | Out-String) | ConvertFrom-Json
    $matching = $containers | Where-Object {
        $_.Config.Labels.'devcontainer.local_folder' -ieq $workspacePath
    } | Sort-Object Created -Descending | Select-Object -First 1
    if ($matching) { $containerId = $matching.Id }
}

if (-not $containerId) {
    $cli = Get-ChildItem (Join-Path $env:USERPROFILE '.vscode/extensions/ms-vscode-remote.remote-containers-*/dist/spec-node/devContainersSpecCLI.js') |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
    $codeCommand = Get-Command code -ErrorAction Stop
    $codeExe = Join-Path (Split-Path $codeCommand.Source) '../Code.exe'
    if (-not $cli -or -not (Test-Path -LiteralPath $codeExe)) {
        throw 'Open this folder in VS Code and select Dev Containers: Reopen in Container first.'
    }
    $previousElectronMode = $env:ELECTRON_RUN_AS_NODE
    try {
        $env:ELECTRON_RUN_AS_NODE = '1'
        $result = & $codeExe $cli.FullName up --workspace-folder $workspacePath --log-level error | Out-String
        if ($LASTEXITCODE -ne 0) { throw "Could not start the CS50 container: $result" }
        $outcome = ($result -split "`n" | Where-Object { $_ -match '^\{.*"outcome"' } | Select-Object -Last 1) | ConvertFrom-Json
        if ($outcome.outcome -ne 'success') { throw "Could not start the CS50 container: $result" }
        $containerId = $outcome.containerId
    }
    finally { $env:ELECTRON_RUN_AS_NODE = $previousElectronMode }
}

& docker start $containerId *> $null
if ($LASTEXITCODE -ne 0) { throw 'Could not start the CS50 container.' }

$workingDirectory = '/workspaces/' + (Split-Path $workspacePath -Leaf)
$currentDirectory = (Get-Location).Path
if ($currentDirectory.StartsWith($workspacePath + '\', [StringComparison]::OrdinalIgnoreCase)) {
    $workingDirectory += '/' + $currentDirectory.Substring($workspacePath.Length + 1).Replace('\', '/')
}

$dockerArguments = @('exec', '-i')
if (-not [Console]::IsInputRedirected -and -not [Console]::IsOutputRedirected) {
    $dockerArguments += '-t'
}
$dockerArguments += @('--workdir', $workingDirectory, $containerId, 'bash', '--login')
if ($Command.Count -gt 0) {
    $dockerArguments += @('-c', 'exec "$@"', '--') + $Command
}
& docker @dockerArguments
exit $LASTEXITCODE
