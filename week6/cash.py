
while True:
 try:
    n = float(input("Change:"))
    if ( n >= 0 ) :
     break
    else :
     print("Please enter a positive number.")
 except ValueError:
    print("Please enter a number.")

n = int(round(n*100))
count = 0

if (n >= 25):
    count = count + n//25
    n = n%25
if ( n >= 10 ):
    count = count + n//10
    n = n%10
if ( n >= 5 ):
    count = count + n//5
    n = n%5

count = count + n
print (count)
