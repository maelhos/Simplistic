

width = 80

final = "\xc9" + (width-2)*"\xcd" + "\xbb" + "\n"


final += chr(186) + (width-2)*" " + chr(186) + "\n"

strr = "Wecome to Simplistic kernel !! "
final += chr(186) + " " + strr + (width-3-len(strr))*" " + chr(186) + "\n"

for _ in range(50):
    final += chr(186) + (width-2)*" " + chr(186) + "\n"

final += chr(200) + (width-2)*chr(205) + chr(188) + "\n"

print(final.encode())