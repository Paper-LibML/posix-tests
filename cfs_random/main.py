import sys
import numpy as np
from scipy.spatial.distance import jensenshannon

def main():
    counts = []
    for line in sys.stdin:
        count = line.split()[-2]
        count = int(count)

        counts.append(count)

    observed = np.array(counts)

    # Normaliza la distribución observada
    P = observed / np.sum(observed)

    # Crea la distribución uniforme
    Q = np.ones_like(P) / len(P)

    # Calcula la Jensen-Shannon divergence
    jsd = jensenshannon(P, Q, base=2)**2  # El cuadrado es para obtener la divergencia real

    print(f"Jensen-Shannon Divergence (JSD): {jsd:.4f}")

if __name__ == '__main__':
    main()
