import matplotlib.pyplot as plt

# Dados hipotéticos (Número de cidades e tempo de execução)
num_cidades = [4, 5, 6, 7, 8, 9, 10]
tempo_backtracking = [0.001, 0.002, 0.003, 0.005, 0.007, 0.01, 0.015]
tempo_brute_force = [0.002, 0.005, 0.01, 0.04, 0.15, 1.2, 10.0]

# Plotar os dados
plt.plot(num_cidades, tempo_backtracking, label='Backtracking', marker='o')
plt.plot(num_cidades, tempo_brute_force, label='Brute Force', marker='o')

plt.xlabel('Número de Cidades')
plt.ylabel('Tempo de Execução (segundos)')
plt.title('Comparação de Tempo: Backtracking vs Brute Force')
plt.legend()
plt.grid(True)
plt.show()
