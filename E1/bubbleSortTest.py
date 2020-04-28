import time
import arrayGen
import sort

print('\nut: Unidades de Tiempo\n')

# ------------------------------------------------------------------------------------------
# Bubble Sort
# ------------------------------------------------------------------------------------------
print('Bubble Sort')
for n in [10, 100, 1000, 10000]:
    start_time = time.time()

    (A, compG, asigG, objcG, mallocG) = arrayGen.genArray(n)
    (compS, asigS, objcS, mallocS)    = sort.bubbleSort(A)

    end_time  = time.time() - start_time

    comp     = compG + compS
    compUT   = comp << 1
    asig     = asigG + asigS
    asigUT   = asig << 3
    objc     = objcG + objcS
    objcUT   = objc * 200
    malloc   = mallocG + mallocS
    mallocUT = 50 + (malloc * 10)

    print(f'\tComparaciones:\t\t\t{comp} = {compUT}ut')
    print(f'\tAsignaciones:\t\t\t{asig} = {asigUT}ut')
    print(f'\tInstancias (objetos):\t\t{objc} = {objcUT}ut')
    print(f'\tEspacio de memoria alojado:\t{malloc} = {mallocUT}ut')
    print(f'\tTotal:\t\t\t\t\t\t{compUT + asigUT + objcUT + mallocUT}ut') # Total

    print('--- %s seconds ---\n' % (end_time))
# ------------------------------------------------------------------------------------------

# ------------------------------------------------------------------------------------------
# Prediccion de tiempos mediante recta de regresion lineal
# ------------------------------------------------------------------------------------------
print('100000, 1000000, ... son muy costosos en la ejecución de este algoritmo')
print("""
Pero de todas formas podemos predecir su comportamiento en caso
se generare el arreglo y se ordene gracias al analisis previo\n
""")
for n in [100000, 1000000, 10000000, 100000000]:
    comp     = n + (n**2 + 2)
    compUT   = comp << 1
    asig     = (2 * n + 1) + (4 * n**2 + 4)
    asigUT   = asig << 3
    objc     = 1 + (n + 1)
    objcUT   = objc * 200
    malloc   = n + 0
    mallocUT = 50 + (malloc * 10)

    print(f'n = {n} =>')
    print(f'\tComparaciones:\t\t\t{comp} = {compUT}ut')
    print(f'\tAsignaciones:\t\t\t{asig} = {asigUT}ut')
    print(f'\tInstancias (objetos):\t\t{objc} = {objcUT}ut')
    print(f'\tEspacio de memoria alojado:\t{malloc} = {mallocUT}ut')
    print(f'\tTotal:\t\t\t\t\t\t{compUT + asigUT + objcUT + mallocUT}ut') # Total
# ------------------------------------------------------------------------------------------
