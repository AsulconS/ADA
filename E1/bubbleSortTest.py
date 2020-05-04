import time
import arrayGen
import sort
import linearAlgebra

def bubbleSortTest():
    # ------------------------------------------------------------------------------------------
    X = [] # Eje de Abscisas para la recta de regresion para predecir los tiempos
    Y = [] # Eje de Ordenadas para la recta de regresion para predecir los tiempos
    # ------------------------------------------------------------------------------------------

    # ------------------------------------------------------------------------------------------
    # Bubble Sort
    # ------------------------------------------------------------------------------------------
    print('Insert Sort')
    for i in [5, 10, 50, 100, 500, 1000, 5000, 10000]:
        start_time = time.time()

        A = arrayGen.genArray(i)
        (comp, asig, objc, malloc) = sort.bubbleSort(A)

        end_time  = time.time() - start_time

        compUT   = comp << 1     # comp << 1 = comp * 2 (Bitwise)
        asigUT   = asig << 3     # asig << 3 = comp * 8 (Bitwise)
        objcUT   = objc * 200
        mallocUT = 50 + (malloc * 10)
        totalUT  = compUT + asigUT + objcUT + mallocUT

        X.append(float(totalUT))
        Y.append(float(end_time))

        print(f'\tComparaciones:\t\t\t{comp} = {compUT}ut')
        print(f'\tAsignaciones:\t\t\t{asig} = {asigUT}ut')
        print(f'\tInstancias (objetos):\t\t{objc} = {objcUT}ut')
        print(f'\tEspacio de memoria alojado:\t{malloc} = {mallocUT}ut')
        print(f'\tTotal:\t\t\t\t\t\t{totalUT}ut') # Total

        print('--- %s seconds ---\n' % (end_time))
    # ------------------------------------------------------------------------------------------

    # ------------------------------------------------------------------------------------------
    # Prediccion de tiempos mediante recta de regresion cuadratica
    # ------------------------------------------------------------------------------------------
    X2 = linearAlgebra.powScaleVector(X, 2)
    X3 = linearAlgebra.powScaleVector(X, 3)
    X4 = linearAlgebra.powScaleVector(X, 4)
    XY = linearAlgebra.vecProd(X, Y)
    X2Y = linearAlgebra.vecProd(X2, Y)
    sumX  = sum(X)
    sumY  = sum(Y)
    sumX2 = sum(X2)
    sumX3 = sum(X3)
    sumX4 = sum(X4)
    sumXY = sum(XY)
    sumX2Y = sum(X2Y)
    n = len(X)

    M = [[n, sumX, sumX2], [sumX, sumX2, sumX3], [sumX2, sumX3, sumX4]]
    B = [sumY, sumXY, sumX2Y]

    V  = linearAlgebra.gauss(M, B)
    w0, w1, w2 = V[0], V[1], V[2]
    # ------------------------------------------------------------------------------------------

    # ------------------------------------------------------------------------------------------
    print('100000, 1000000, ... son muy costosos en la ejecución de este algoritmo')
    print("Para ello mediante el metodo de minimos cuadrados obtuvimos 3 parametros")
    print("Estos 3 parametros dan forma a la ecuacion cuadratica de tiempos del tipo:")
    print("w0 + w1 * ut + w2 * ut^2\n")
    for n in [100000, 1000000, 10000000, 100000000]:
        comp     = n**2 + 2 * n - 2
        compUT   = comp << 1
        asig     = n**2 + 3 * n - 2
        asigUT   = asig << 3
        objc     = 0
        objcUT   = objc * 200
        malloc   = 0
        mallocUT = 50 + (malloc * 10)
        totalUT  = compUT + asigUT + objcUT + mallocUT

        print(f'n = {n} =>')
        print(f'\tComparaciones:\t\t\t{comp} = {compUT}ut')
        print(f'\tAsignaciones:\t\t\t{asig} = {asigUT}ut')
        print(f'\tInstancias (objetos):\t\t{objc} = {objcUT}ut')
        print(f'\tEspacio de memoria alojado:\t{malloc} = {mallocUT}ut')
        print(f'\tTotal:\t\t\t\t\t\t{totalUT}ut') # Total

        print(f'--- {w0 + w1 * totalUT + w2 * totalUT**2} seconds ---\n')

    print("Gracias a ello pudimos predecir todas las ultimas medidas")

    return (w0, w1, w2)
    # ------------------------------------------------------------------------------------------
