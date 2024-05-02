import krpc
import matplotlib.pyplot as plt
import time as t

# Подключение к серверу kRPC
conn = krpc.connect('altitude_check')

# Получение объекта космического корабля
vessel = conn.space_center.active_vessel

# Создание массивов для данных о времени и высоте
time_values = []
altitude_values = []
time = 0

# Получение высоты корабля на протяжении полета
while True:
    # Получение текущей высоты
    altitude = vessel.flight().surface_altitude
    time_values.append(time)  # Запись текущего времени в массив
    altitude_values.append(altitude)  # Запись текущей высоты в массив

    # Вывод считываемых данных в консоль
    print("Время: {}, Высота: {} м".format(time, altitude))
    t.sleep(1)
    time += 1
    # Проверка условия завершения сбора данных
    if altitude > 100000:  # Остановка считывания данных при наборе высоты 100км
        break

    # Построение графика скорости от времени
plt.plot(time_values, altitude_values)
plt.title('Зависимость высоты от времени')
plt.xlabel('Время, s')
plt.ylabel('Высота, m')
plt.show()
