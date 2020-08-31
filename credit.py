from cs50 import *
n = get_int("Number: ")
print()
#print(f"n = {n}")
first_digits = n % 100
sum1 = sum2 = i = 0

if n > 10**12:
    print("INVALID")
    exit()
while n != 0:
    if i % 2 == 0:
        sum2 += n % 10
        #print(f"sum2 now is: {sum2}")
    else:
        sum1 += (2 * (n % 10))%10 + (2 * (n % 10))//10
        #print(f"sum1 now is: {sum1}")
    i += 1
    n = n // 10

Luhn_valid = (sum1+sum2) % 10 == 0
#print(f"sum1 = {sum1}, sum2 = {sum2}")
if Luhn_valid:
    if first_digits % 10 == 4:
        print("VISA")
    elif first_digits >= 51 and first_digits <= 55:
        print("MASTERCARD")
    elif first_digits == 34 or first_digits == 37 or first_digits == 31 or first_digits % 10 == 5:
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")
