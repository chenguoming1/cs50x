if __name__ == "__main__":
    cc = input("Number: ")
    # print(len(cc))
    sum = 0
    # print('---------------')
    # 4 0 0 3 6 0 0 0 0 0 0 0 0 0 1 4
    for i in range(len(cc)-2, -1, -2):
        val = int(cc[i]) * 2
        sum = sum + (val - 9 if val > 9 else val)
        # print(i, ":", int(cc[i]), "*", 2, "=", val, ' fval: ',  (val - 9 if val > 9 else val))
    # print('---------------')
    # print(sum)

    # print('---------------')
    sum2 = 0
    for i in range(len(cc)-1, -1, -2):
        sum2 = sum2 + int(cc[i])
        # print(i,":", int(cc[i]), int(cc[i]))
    # print('---------------')
    # print(sum2)

    # print(sum+sum2)
    modulo = (sum + sum2) % 10
    # print('modulo', modulo)
    if modulo == 0:
        # print('digit: ', cc[:2], ' len:', len(cc))
        if (int(cc[:2]) == 32 or int(cc[:2]) == 37) and len(cc) == 15:
            print('AMEX')
        elif int(cc[0]) == 4 and (len(cc) == 13 or len(cc) == 16):
            print('VISA')
        elif (int(cc[:2]) == 51 or int(cc[:2]) == 52 or int(cc[:2]) == 53 or int(cc[:2]) == 54 or int(cc[:2]) == 55) and len(cc) == 16:
            print('MASTERCARD')
        else:
            print('INVALID')
    else:
        print('INVALID')
