import matplotlib.pyplot as plt
import networkx as nx

# Minimax function
def minimax(state, is_maximizing, depth=0):
    x, y = state
    if x == 0 and y == 0:  # Terminal state
        return -depth if is_maximizing else depth

    # All possible moves
    moves = []
    for i in range(1, x + 1):
        moves.append((x - i, y))  # Take marbles from pile 1
    for j in range(1, y + 1):
        moves.append((x, y - j))  # Take marbles from pile 2

    # Sort moves according to problem criteria
    moves.sort(key=lambda s: (sum(s), max(s)))

    # Minimax logic
    if is_maximizing:
        best_value = float('-inf')
        for move in moves:
            value = minimax(move, False, depth + 1)
            best_value = max(best_value, value)
    else:
        best_value = float('inf')
        for move in moves:
            value = minimax(move, True, depth + 1)
            best_value = min(best_value, value)

    return best_value

# Alpha-beta pruning function
def alpha_beta(state, is_maximizing, alpha=float('-inf'), beta=float('inf'), depth=0):
    x, y = state
    if x == 0 and y == 0:  # Terminal state
        return -depth if is_maximizing else depth

    # All possible moves
    moves = []
    for i in range(1, x + 1):
        moves.append((x - i, y))  # Take marbles from pile 1
    for j in range(1, y + 1):
        moves.append((x, y - j))  # Take marbles from pile 2

    # Sort moves according to problem criteria
    moves.sort(key=lambda s: (sum(s), max(s)))

    if is_maximizing:
        best_value = float('-inf')
        for move in moves:
            value = alpha_beta(move, False, alpha, beta, depth + 1)
            best_value = max(best_value, value)
            alpha = max(alpha, best_value)
            if beta <= alpha:  # Prune
                break
        return best_value
    else:
        best_value = float('inf')
        for move in moves:
            value = alpha_beta(move, True, alpha, beta, depth + 1)
            best_value = min(best_value, value)
            beta = min(beta, best_value)
            if beta <= alpha:  # Prune
                break
        return best_value

# Function to generate and draw the minimax tree using networkx
def generate_tree(state, is_maximizing, alpha_beta_pruning=False):
    G = nx.DiGraph()

    def add_edges(state, is_maximizing, parent=None, alpha=float('-inf'), beta=float('inf')):
        x, y = state
        node_label = f"({x}, {y})"
        if parent:
            G.add_edge(parent, node_label)
        if x == 0 and y == 0:  # Terminal state
            return

        moves = []
        for i in range(1, x + 1):
            moves.append((x - i, y))
        for j in range(1, y + 1):
            moves.append((x, y - j))

        moves.sort(key=lambda s: (sum(s), max(s)))

        for move in moves:
            next_label = f"({move[0]}, {move[1]})"
            if alpha_beta_pruning:
                if is_maximizing:
                    alpha = max(alpha, alpha_beta(move, False))
                    if beta <= alpha:  # Prune
                        G.add_edge(node_label, next_label, label="Pruned")
                        break
                else:
                    beta = min(beta, alpha_beta(move, True))
                    if beta <= alpha:  # Prune
                        G.add_edge(node_label, next_label, label="Pruned")
                        break

            add_edges(move, not is_maximizing, node_label, alpha, beta)

    add_edges(state, is_maximizing)
    return G

# Function to plot the tree
def plot_tree(G):
    pos = nx.spring_layout(G)
    plt.figure(figsize=(12, 8))
    labels = nx.get_edge_attributes(G, 'label')
    nx.draw(G, pos, with_labels=True, node_size=3000, node_color='lightblue', font_size=10, font_weight='bold')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()

# Initial state (2 marbles in each pile)
initial_state = (2, 2)

# Generate and plot minimax tree
minimax_tree = generate_tree(initial_state, True)
plot_tree(minimax_tree)

# Generate and plot alpha-beta pruned tree
alpha_beta_tree = generate_tree(initial_state, True, alpha_beta_pruning=True)
plot_tree(alpha_beta_tree)
