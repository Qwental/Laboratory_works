import krpc
import matplotlib.pyplot as plt

# Подключение к серверу kRPC
conn = krpc.connect('cheker')

# Получение объекта космического корабля
vessel = conn.space_center.active_vessel

# Создание массивов для данных о времени и скорости
time_values = []
speed_values = []

# Получение скорости корабля на протяжении полета
while True:
    time = conn.space_center.ut  # Получение данных о текущем времени
    speed = vessel.flight(vessel.orbit.body.reference_frame).speed  # Получение текущей скорости
    time_values.append(time)  # Запись текущего времени в массив
    speed_values.append(speed)  # Запись текущей скорости в массив
    print("Время: {}, Скорость корабля: {} м/с".format(time, speed))  # Вывод считываемых данных в консоль

    # Проверка условия завершения сбора данных
    altitude = vessel.flight().surface_altitude
    if altitude > 100000:  # Остановка считывания данных при наборе высоты 100км
        break

    # Построение графика скорости от времени
plt.plot(time_values, speed_values)
plt.title('Зависимость скорости от времени')
plt.xlabel('Время, s')
plt.ylabel('Скорость, m/s')
plt.show()
