card = input ("Enter the card number:")
count = 0
sum = 0
c = card

if ( card.isdigit() ):
 for dig in reversed(card):
   last = int(dig)
   count += 1
   if ( count%2 == 0 ):
     tmp = last*2
     if ( tmp > 9 ):
       x = tmp%10
       tmp = tmp//10
       sum = sum + tmp + x
     else:
       sum = sum + tmp
   else:
     sum = sum + last

 if (sum%10 == 0):
  if ( len(card) == 15 and (card[:2]=="34" or card[:2]=="37") ):
   print ("AMEX")
  elif ( len(card) == 16 and ( card[:2]=="51" or card[:2]=="55") ):
   print ("MASTERCARD")
  elif ( ( len(card) == 16 or len(card) == 13 ) and card[0] == "4" ):
   print ("VISA")
  else:
   print ("INVALID")
 else:
  print ("INVALID")

else :
 print ("INVALID")




