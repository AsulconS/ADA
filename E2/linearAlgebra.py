def addScalarVector(V, s):
    return [v + s for v in V]

def scaleVector(V, s):
    return [v * s for v in V]

def powScaleVector(V, p):
    return [v ** p for v in V]

def vecSum(V1, V2):
    return [v1 + v2 for (v1, v2) in zip(V1, V2)]

def vecSub(V1, V2):
    return [v1 - v2 for (v1, v2) in zip(V1, V2)]

def vecProd(V1, V2):
    return [v1 * v2 for (v1, v2) in zip(V1, V2)]

def vecTrueDiv(V1, V2):
    return [v1 / v2 for (v1, v2) in zip(V1, V2)]

def vecFloorDiv(V1, V2):
    return [v1 // v2 for (v1, v2) in zip(V1, V2)]

def dotProd(V1, V2):
    return sum(vecProd(V1, V2))

def rs(A, B):
    n = len(B)
    X = [0] * n

    for i in range(n - 1, -1, -1):
        s = 0
        for k in range(i + 1, n):
            s = s + A[i][k] * X[k]
        X[i] = (B[i] - s) / A[i][i]
    return X

def triangulate(A, B):
    n = len(B)
    GA = A
    GB = B
    for i in range(n):
        for k in range(i + 1, n):
            f = -GA[k][i]
            for j in range(i, n):
                GA[k][j] = GA[k][j] + (GA[i][j] / GA[i][i]) * f
            GB[k] = GB[k] + (GB[i] / GA[i][i]) * f
    return (GA, GB)

def gauss(A, B):
    (GA, GB) = triangulate(A, B)
    return rs(GA, GB)

# No mutable
class MatVector:
    def __init__(self, data):
        self.data = data
        self.length = len(data)

    def __add__(self, o):
        return MatVector(vecSum(self.data, o.data))

    def __sub__(self, o):
        return MatVector(vecSub(self.data, o.data))

    def __mul__(self, o):
        return MatVector(vecProd(self.data, o.data))

    def __truediv__(self, o):
        return MatVector(vecTrueDiv(self.data, o))

    def __floordiv__(self, o):
        return MatVector(vecFloorDiv(self.data, o))

    def __pow__(self, o):
        return MatVector(powScaleVector(self.data, o))

    def addScalar(self, s):
        return MatVector(addScalarVector(self.data, s))

    def scale(self, s):
        return MatVector(scaleVector(self.data, s))

    @staticmethod
    def multipleValues(val, size):
        return MatVector([val] * size)
