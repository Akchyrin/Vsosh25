import cv2
from serial import Serial
from PIL import Image
a = "No"

ser = Serial('COM3', 9600, timeout = 0.1)

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
            response = int(response)
            if response == 1000000:
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
# считываем сигнал ардуинки с колличеством подъёмов в ряду
response = 0
n = 0
while int(response) == 0:
    try:
        response = ser.readline().decode('utf-8')
        if response:
            n = int(response)
            print(n)
    except:
        print('error')

print("начало склейки")

def grid_n_from_nomer(n, nomer):
    # n     - кол-во фото в столбце
    # nomer - общее кол-во фото

    images = [Image.open(f'file_cadr_obrez_namber_{i}.jpg') for i in
              range(1, nomer + 1)]

    #
    # images =[]
    # for i in range(1, nomer + 1):
    #     images = Image.open(f'file_cadr_obrez_namber_{i}.jpg')
    #     images.append(Image)
    #
    # n - количество строк = сколько фото в столбике
    m = (nomer // n) + 1  # количество столбцов

    # размеры изображений
    width, height = images[0].size

    # Пустое изображение, куда будем вставлять фотки
    grid_image = Image.new('RGB', (m * width, n * height))
    print(m)
    # Заполнение сетки
    for index, img in enumerate(images):
        col = m - 1 - (index // n)  # Определяем столбец
        row = n - 1 - (index % n)  # Определяем строку (снизу вверх)

        if col < m and row >= 0:  # Проверяем, чтобы не выйти за пределы
            grid_image.paste(img, (col * width, row * height))

    grid_image.save('grid_image_3.jpg')
    # grid_image.show()


grid_n_from_nomer(n, nomer)
print("конец склейки")
