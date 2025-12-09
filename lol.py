from math import sqrt

n = int(input())
atom = "Au" # Тип атома
a = 1 # Расстояние между атомами

atoms = []
with open("output.xyz", "w") as f:
    # Начальные x0, y0
    k = 1
    xk = 0
    zk = 0
    # Расстояние между слоями sqrt(2) / 2 * a
    h = sqrt(2) / 2 * a
    # Строим слои сверху вниз до слоя, содержащего n^2 атомов
    for i in range(n - 1, -1, -1):
        y = i * h
        for j in range(k):
            for l in range(k):
                atoms.append([xk - j * a, y, zk - l * a])
        # Переходим от k-ого слоя к k+1-ому
        xk += a / 2
        zk += a / 2
        k += 1

    xk -= a
    zk -= a
    k -= 2

    # Строим оставшиеся слои
    for i in range(n - 1):
        y = -(i + 1) * h
        for j in range(k):
            for l in range(k):
                atoms.append([xk - j * a, y, zk - l * a])
        xk -= a / 2
        zk -= a / 2
        k -= 1

    f.write(str(len(atoms)) + "\n") # Количество атомов
    f.write("NANO CLASTER\n") # Комментарий
    for i in atoms:
        f.write(atom + " " + f'{i[0]:.9f}' + " " + f'{i[1]:.9f}' + " " + f'{i[2]:.9f}' + "\n") # Координаты атомов
