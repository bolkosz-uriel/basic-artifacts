# i was boared so here is a calculator anyways..........

# gui_calculator_fixed.py

import math
import tkinter as tk
from tkinter import messagebox


def safe_eval(expression: str) -> float:
    """Safely evaluates a mathematical expression."""
    try:
        # Replace power operator for proper evaluation
        expression = expression.replace('^', '**')

        # Allow only specific characters and function names
        allowed_functions = {"sin", "cos", "tan", "sqrt"}
        allowed_chars = set("0123456789+-*/(). ")

        # Split expression into tokens for validation
        tokens = expression.replace("(", " ").replace(")", " ").split()
        for token in tokens:
            if token.isalpha() and token not in allowed_functions:
                raise ValueError(f"Invalid function: {token}")
        
        # Check for disallowed characters
        for char in expression:
            if char not in allowed_chars and not char.isalpha():
                raise ValueError(f"Invalid character: {char}")

        # Evaluate safely with allowed math functions
        return eval(expression, {"__builtins__": None}, {
            "sqrt": math.sqrt,
            "sin": lambda x: math.sin(math.radians(x)),
            "cos": lambda x: math.cos(math.radians(x)),
            "tan": lambda x: math.tan(math.radians(x))
        })
    except ZeroDivisionError:
        raise ValueError("Division by zero is not allowed.")
    except Exception as e:
        raise ValueError(f"Invalid input: {str(e)}")


def evaluate_input():
    """Handles the evaluation of the user input."""
    expression = entry.get().strip()
    try:
        if not expression:
            raise ValueError("Expression cannot be empty.")
        result = safe_eval(expression)
        result_label.config(text=f"Result: {result}")
    except ValueError as e:
        result_label.config(text="Result: Error")
        messagebox.showerror("Error", str(e))


def insert_function(function_name):
    """Insert the selected function into the entry field."""
    current_text = entry.get()
    if current_text and current_text[-1].isalpha():
        return  # Prevent inserting another function without parentheses
    entry.insert(tk.END, f"{function_name}(")


# GUI Setup
root = tk.Tk()
root.title("Secure Calculator")

# Entry Field at the Top
entry_frame = tk.Frame(root, padx=10, pady=10)
entry_frame.pack(fill=tk.X)

entry_label = tk.Label(entry_frame, text="Enter Expression:")
entry_label.pack(side=tk.LEFT)

entry = tk.Entry(entry_frame, width=30)
entry.pack(side=tk.LEFT, fill=tk.X, expand=True)

# Buttons and Result Layout
main_frame = tk.Frame(root, padx=10, pady=10)
main_frame.pack(fill=tk.X)

# Buttons on the Left
button_frame = tk.Frame(main_frame)
button_frame.pack(side=tk.LEFT, anchor="nw")

sin_button = tk.Button(button_frame, text="sin", command=lambda: insert_function("sin"))
sin_button.pack(fill=tk.X, pady=5)

cos_button = tk.Button(button_frame, text="cos", command=lambda: insert_function("cos"))
cos_button.pack(fill=tk.X, pady=5)

tan_button = tk.Button(button_frame, text="tan", command=lambda: insert_function("tan"))
tan_button.pack(fill=tk.X, pady=5)

sqrt_button = tk.Button(button_frame, text="sqrt", command=lambda: insert_function("sqrt"))
sqrt_button.pack(fill=tk.X, pady=5)

calculate_button = tk.Button(button_frame, text="Calculate", command=evaluate_input)
calculate_button.pack(fill=tk.X, pady=10)

exit_button = tk.Button(button_frame, text="Exit", command=root.quit)
exit_button.pack(fill=tk.X, pady=5)

# Result Display on the Right
result_frame = tk.Frame(main_frame)
result_frame.pack(side=tk.RIGHT, anchor="ne", fill=tk.BOTH, expand=True)

result_label = tk.Label(result_frame, text="Result: ", fg="blue", anchor="w", justify="left", padx=10)
result_label.pack(side=tk.RIGHT, anchor="ne", padx=10, pady=10)

root.mainloop()
