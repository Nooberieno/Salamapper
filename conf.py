# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'salamapper'
copyright = '2024, Nooberieno'
author = 'Nooberieno'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']

extensions = [
	'breathe'
	'myst_parser'
]

breathe_projects = {
	"salamapper": "xml"
}
breathe_default_project = "salamapper"

myst_enable_extensions = [
    "deflist",
    "fieldlist",
    "linkify",
    "replacements",
    "substitution",
    "tasklist"
]
