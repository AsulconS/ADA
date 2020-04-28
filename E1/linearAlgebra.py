def scale(V, s):
    return [v * s for v in V]

def powScale(V, p):
    return [v**p for v in V]

def vecProdScale(V1, V2):
    return [v1 * v2 for (v1, v2) in zip(V1, V2)]

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
