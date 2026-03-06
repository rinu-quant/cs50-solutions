while True:
 try:
  n = input("Enter the height :")
  if ( n.isdigit() ):
   n = int(n)
   if ( n < 9 and n > 0 ):
    break
 except ValueError:
   print ("Enter an integer ")

for i in range ( 1 , n+1):

  print (" " * (n-i) , end='')

  print ("#" * i , end='')

  print ("  " , end='')

  print ("#" * i )
