import cv2
from serial import Serial
a = "No"

ser = Serial('COM4', 9600, timeout = 0.1)

cap = cv2.VideoCapture(0)
nomer = 0

x_razm = 405
y_razm = 544
obl_x = 249
obl_y = 106
x1 = x_razm - obl_x
x1 = x1 // 2
x2 = x_razm - obl_x
x2 = x2 // 2
x2 = x_razm - x2
y1 = y_razm - obl_y
y1 = y1 // 2
y2 = y_razm - obl_y
y2 = y2 // 2
y2 = y_razm - y2

response = 1
while response != 2000000:
    try:
        response = ser.readline().decode('utf-8')
        if response:
            print(int(response))
            if int(response) == 1000000:
                print("Ok")
                a = "Ok"
                nomer = nomer + 1
                nazwanie_faila = "file_cadr_namber_" + str(nomer) + ".jpg"
                ret, img = cap.read()
                cv2.imshow("fds", img)
                print(nomer)
                # cv2.waitKey(1000)
                cv2.imwrite(nazwanie_faila, img)
                img_obrez = img[y1:y2, x1:x2]
                nazwanie_faila_obrez = "file_cadr_obrez_namber_" + str(nomer) + ".jpg"
                cv2.imwrite(nazwanie_faila_obrez, img_obrez)
            else:
                a = "No"
    except:
        print('error')
