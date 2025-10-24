para = input("Enter the paragraph :")

lc = 0
wc = 0
sc = 0
t = False

for char in para:
    if char.isalpha():
       lc += 1
       t = True
    if char in " ,.:;!?":
       if t :
         wc += 1
         t = False
    if char in ".?!":
       sc += 1
if t:
  wc += 1

L = (lc/wc)*100
S = (sc/wc)*100
index = round((0.0588 * L) - (0.296 * S) - 15.8)

if ( index < 1 ):
   print ( "Before Grade 1" )
elif ( index >= 16 ):
   print ("Grade 16+")
else:
   print ("Grade",index )
