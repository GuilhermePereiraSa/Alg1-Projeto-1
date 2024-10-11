import matplotlib.pyplot as plt
import networkx as nx

# Função para desenhar a árvore de força bruta
def desenhar_arvore_forca_bruta(G, pos):
    plt.figure(figsize=(10, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=500, font_size=10, font_weight='bold')
    plt.title("Árvore de Soluções - Força Bruta (Sem Poda)", fontsize=14)
    plt.show()

# Função para desenhar a árvore de backtracking (com poda)
def desenhar_arvore_backtracking(G, pos, podas):
    plt.figure(figsize=(10, 6))
    nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=500, font_size=10, font_weight='bold')
    
    # Destacar as arestas podadas
    nx.draw_networkx_edges(G, pos, edgelist=podas, edge_color='red', style='dashed', width=2, label='Podas')
    
    plt.title("Árvore de Soluções - Backtracking (Com Poda)", fontsize=14)
    plt.show()

# Criando a árvore de soluções (tanto para força bruta quanto backtracking)
G = nx.DiGraph()

# Nós e arestas de uma árvore genérica para ilustrar as diferenças
edges = [
    (1, 2), (1, 3), (1, 4),
    (2, 5), (2, 6), (3, 7), (3, 8), (4, 9), (4, 10),
    (5, 11), (6, 12), (7, 13), (8, 14), (9, 15), (10, 16)
]

G.add_edges_from(edges)

# Posicionamento dos nós na árvore
pos = {
    1: (0, 3), 2: (-3, 2), 3: (0, 2), 4: (3, 2),
    5: (-4, 1), 6: (-2, 1), 7: (-1, 1), 8: (1, 1), 9: (2, 1), 10: (4, 1),
    11: (-4.5, 0), 12: (-2.5, 0), 13: (-1.5, 0), 14: (0.5, 0), 15: (2.5, 0), 16: (4.5, 0)
}

# Arestas podadas no backtracking
podas = [(3, 7), (2, 6)]

# Gerando o gráfico de força bruta
desenhar_arvore_forca_bruta(G, pos)

# Gerando o gráfico de backtracking com poda
desenhar_arvore_backtracking(G, pos, podas)
