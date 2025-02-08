import os
import re
import datetime

# Define authors
authors = ["Matteo Gottardelli", "Niccolò Cristoforetti", "Alessandro Benassi", "Daniele Calvo"]  # Customize your authors here
date = datetime.date.today().strftime("%Y-%m-%d")  # Auto-generates today's date

# Function to generate Doxygen comments
def generate_doxygen_comments(code, is_header=False):
    """
    Generates Doxygen comments for C++ function declarations (header) or definitions (c).
    """
    # Regex patterns for function declarations and definitions
    if is_header:
        pattern = r"(\w+(?:\s*\*?)\s+\w+)\(([^)]*)\)\s*;"
    else:
        pattern = r"(\w+(?:\s*\*?)\s+\w+)\(([^)]*)\)\s*\{"

    functions = re.findall(pattern, code)
    generated_comments = []

    for return_type, params in functions:
        param_list = params.split(", ") if params else []
        
        # Build the Doxygen comment
        comment = "/**\n * @brief TODO: Describe function.\n"
        
        for param in param_list:
            if param:
                param_name = param.split()[-1]  # Extract variable name
                comment += f" * @param {param_name} TODO: Describe parameter.\n"

        if return_type.strip() != "void":
            comment += " * @return TODO: Describe return value.\n"

        # Add authors and date
        for author in authors:
            comment += f" * @author {author}\n"
        comment += f" * @date {date}\n"
        comment += " */"

        # Place comments before function declarations or definitions
        if is_header:
            generated_comments.append(f"{comment}\n{return_type}({params});")
        else:
            generated_comments.append(f"{comment}\n{return_type}({params}) {{\n    // Function code\n}}")

    return "\n\n".join(generated_comments)

# Function to process all C++ files in a folder
def process_c_folder(folder_path):
    if not os.path.isdir(folder_path):
        print(f"❌ Error: The folder '{folder_path}' does not exist!")
        return
    
    output_folder = os.path.join(folder_path, "documented")
    os.makedirs(output_folder, exist_ok=True)  # Create output folder if it doesn't exist

    for filename in os.listdir(folder_path):
        if filename.endswith(".c") or filename.endswith(".h"):
            file_path = os.path.join(folder_path, filename)

            with open(file_path, "r", encoding="utf-8") as file:
                c_code = file.read()

            is_header = filename.endswith(".h")
            documented_code = generate_doxygen_comments(c_code, is_header)

            # Save output in the 'documented' folder
            output_file = os.path.join(output_folder, filename)
            with open(output_file, "w", encoding="utf-8") as file:
                file.write(documented_code)

            print(f"✅ Processed: {filename} → Saved to 'documented/{filename}'")

# Example usage
folder_path = "./general"  # Replace with your actual folder path
process_c_folder(folder_path)
