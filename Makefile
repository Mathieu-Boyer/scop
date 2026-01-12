#---------------------------------Directories---------------------------------#
OBJS_DIR    = .objs
DEPS_DIR    = .deps
SRCS_DIR    = src
HEADER_DIR  = include

#---------------------------------Binary---------------------------------#
NAME        = scop

#---------------------------------Compiler---------------------------------#
CC          = c++
RM          = rm -f

CFLAGS      = -Wall -Wextra -Werror -std=c++20 -MMD -MP -O0 -g

#---------------------------------Includes---------------------------------#
INCLUDES    = -I$(HEADER_DIR) -I$(HEADER_DIR)/classes

#---------------------------------Libraries (LINUX)---------------------------------#
LDFLAGS     =
LDLIBS      = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

#---------------------------------Sources---------------------------------#
SRCS = \
	$(SRCS_DIR)/Camera.cpp \
	$(SRCS_DIR)/GLApp.cpp \
	$(SRCS_DIR)/LinearAlgebra.cpp \
	$(SRCS_DIR)/main.cpp \
	$(SRCS_DIR)/Mesh.cpp \
	$(SRCS_DIR)/OBJParser.cpp \
	$(SRCS_DIR)/PPMParser.cpp \
	$(SRCS_DIR)/Renderable.cpp \
	$(SRCS_DIR)/Scene.cpp \
	$(SRCS_DIR)/Shaders.cpp \
	$(SRCS_DIR)/Texture.cpp \
	$(SRCS_DIR)/transform.cpp \
	$(SRCS_DIR)/utils.cpp

#---------------------------------Objects---------------------------------#
OBJS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

#---------------------------------Pretty---------------------------------#
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
RESET   = \033[0m
UP      = \033[A
CUT     = \033[K

#---------------------------------Rules---------------------------------#
all: $(NAME)

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)$(RESET)"
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@$(RM) $(OBJS)
	@rm -rf $(OBJS_DIR)
	@printf "$(UP)$(CUT)"

fclean: clean
	@echo "$(YELLOW)Removing executable$(RESET)"
	@$(RM) $(NAME)
	@printf "$(UP)$(CUT)"

re: fclean all

.PHONY: all clean fclean re
