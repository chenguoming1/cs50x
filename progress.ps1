# Refresh the local file scan and open your offline progress tracker in Chrome.
$ErrorActionPreference = 'Stop'
& python (Join-Path $PSScriptRoot 'scripts/progress.py')
if ($LASTEXITCODE -ne 0) { throw 'The progress tracker could not be refreshed.' }
$pagePath = Join-Path $PSScriptRoot 'progress.html'
$chromePath = @(
    (Join-Path $env:ProgramFiles 'Google/Chrome/Application/chrome.exe'),
    (Join-Path ${env:ProgramFiles(x86)} 'Google/Chrome/Application/chrome.exe'),
    (Join-Path $env:LOCALAPPDATA 'Google/Chrome/Application/chrome.exe')
) | Where-Object { Test-Path -LiteralPath $_ } | Select-Object -First 1
if ($chromePath) {
    Start-Process -FilePath $chromePath -ArgumentList @('--new-tab', ([Uri]$pagePath).AbsoluteUri)
}
else { Start-Process -FilePath $pagePath }
