OS := $(shell uname)
BRANCH := $(shell git rev-parse --abbrev-ref HEAD)

.PHONY: default
default: help

.PHONY: help
help:
	echo $(OS) $(BRANCH)
	@echo
	@echo "The most common targets are:"
	@echo
	@echo "- install                 Install node dependencies"
	@echo "- serve                   Start dev server for running examples and tests"
	@echo "- test                    Run unit tests in the console"
	@echo "- check                   Perform a number of checks on the code"
	@echo "- clean                   Remove generated files"
	@echo "- help                    Display this help message"
	@echo
	@echo "Other less frequently used targets are:"
	@echo
	@echo "- build                   Build mylib.js, mylib-debug.js, mylib.js.map and mylib.css"
	@echo "- lint                    Check the code with the linter"
	@echo "- ci                      Run the full continuous integration process"
	@echo "- apidoc                  Build the API documentation using JSDoc"
	@echo "- cleanall                Remove all the build artefacts"
	@echo "- check-deps              Check if the required dependencies are installed"
	@echo

.PHONY: apidoc
apidoc: build/timestamps/jsdoc-$(BRANCH)-timestamp

.PHONY: build
build: build/jslib.css build/jslib.js build/jslib-debug.js build/jslib.js.map

.PHONY: check
check: lint build/ol.js test

.PHONY: check-examples
check-examples: $(CHECK_EXAMPLE_TIMESTAMPS)
