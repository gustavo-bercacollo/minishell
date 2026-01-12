#!/usr/bin/env python3
import os
import sys
import re

HEADER_TEMPLATE = """/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {filename:51} :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:00:00 by klima-do          #+#    #+#             */
/*   Updated: 2026/01/12 00:00:00 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

"""

def has_header(content):
    return content.startswith('/* *****************************')

def add_header(filepath, content):
    filename = os.path.basename(filepath)
    header = HEADER_TEMPLATE.format(filename=filename)
    
    # Remove old header if exists
    if has_header(content):
        lines = content.split('\n')
        # Find end of header (line with */)
        for i, line in enumerate(lines):
            if i > 0 and line.strip() == '/* ************************************************************************** */':
                content = '\n'.join(lines[i+1:]).lstrip('\n')
                break
    
    return header + content

def fix_spaces_tabs(content):
    lines = content.split('\n')
    fixed = []
    
    for line in lines:
        # Don't modify empty lines or lines that are only whitespace
        if not line or line.isspace():
            fixed.append('')
            continue
            
        # Remove trailing whitespace
        line = line.rstrip()
        
        fixed.append(line)
    
    return '\n'.join(fixed)

def process_file(filepath):
    try:
        with open(filepath, 'r') as f:
            content = f.read()
        
        # Add/fix header
        content = add_header(filepath, content)
        
        # Fix spaces/tabs
        content = fix_spaces_tabs(content)
        
        # Ensure file ends with newline
        if not content.endswith('\n'):
            content += '\n'
        
        with open(filepath, 'w') as f:
            f.write(content)
        
        print(f"✓ {filepath}")
        return True
    except Exception as e:
        print(f"✗ {filepath}: {e}")
        return False

def main():
    src_dir = 'src'
    
    for root, dirs, files in os.walk(src_dir):
        for file in files:
            if file.endswith('.c'):
                filepath = os.path.join(root, file)
                process_file(filepath)

if __name__ == '__main__':
    main()
