import random

# Del analisis hecho en la parte de abajo, pude generalizar una complejidad en el peor caso de:
# Comparaciones: n      : O(n)
# Asignaciones:  2n + 1 : O(n)
# Instancias:    1      : O(1)
# Alojamiento:   n      : O(n)
def genArray(n, mode, a = 0, b = 100):
    # -----------------------------------------------------------------------------------------------
    comp = 0
    asig = 0
    objc = 0
    malloc = 0
    # -----------------------------------------------------------------------------------------------
    if mode == 'c':
        return list(range(n))
    elif mode == 'd':
        return list(range(n - 1, -1, -1))

    A = [None] * n
    # -----------------------------------------------------------------------------------------------
    asig = asig + 1     # Primera asignacion del i en el for de bajo (linea 22)
    objc = objc + 1     # Alojamiento de memoria del range como objeto iterativo (linea 22)
    malloc = malloc + n # Coste relativo n de crear un arreglo A con n elementos (linea 16)
    # -----------------------------------------------------------------------------------------------
    for i in range(n):
        A[i] = random.randint(a, b)
        # -------------------------------------------------------------------------------------------
        comp = comp + 1 # Comparacion del for anterior para evaluar si esta en el rango (linea 22) +
        asig = asig + 2 # A[i] = rand (linea 23) +
                        # El aumento iterativo del for (i) (ref. linea 22)
        # -------------------------------------------------------------------------------------------

    return A
