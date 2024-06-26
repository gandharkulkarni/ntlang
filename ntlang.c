/* project01.c - initial parsing implemenation */

#include "ntlang.h"

int main(int argc, char **argv) {
    struct config_st config;
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    uint32_t value;
    
    parse_args(&config, argc, argv);

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, config.input);
    
    parse_table_init(&parse_table);
    parse_tree = parse_program(&parse_table, &scan_table);

    value = eval(parse_tree);
    eval_print(&config, value);

    return 0;
}

void ntlang_error(char* err){
	printf(" %s\n", err);
    exit(-1);
}

void print_usage(){
	printf("Usage: project01 <expression>\n");
    printf("  Example: project01 \"1 + 2\"\n");
}

char* get_arg_value(int *i, int argc, char **argv, char *flag){
    (*i) += 1;
    if (*i < argc) {
        return argv[*i];
    } else {
    	char error_message[50];
        sprintf(error_message, "No expression given after flag %s", flag);
   	 	ntlang_error(error_message);
        exit(-1);
    }
}

void parse_args(struct config_st *cp, int argc, char **argv) {
    int i = 1;

    if (argc <= 2) {
        print_usage();
        exit(0);
    }
    
    /* Initializing unsigned flag to false  */
    cp->unsigned_flag = false;
    /* Initializing base to 10  */
    cp->base = 10;
    /* Initializing width to 32  */
    cp->width = 32;

    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'e') {
        	char *arg_value = get_arg_value(&i, argc, argv, "-e");
       		strncpy(cp->input, arg_value, SCAN_INPUT_LEN);
        } else if (argv[i][0] == '-' && argv[i][1] == 'b') {
        	char *arg_value = get_arg_value(&i, argc, argv, "-b");
        	cp->base = (int) convert_string_to_uint32(arg_value, 10);
        } else if (argv[i][0] == '-' && argv[i][1] == 'w') {
        	char *arg_value = get_arg_value(&i, argc, argv, "-w");
        	cp->width = (int) convert_string_to_uint32(arg_value, 10);
        } else if (argv[i][0] == '-' && argv[i][1] == 'u') {
       		cp->unsigned_flag = true;
       	}

        i += 1;
    }

    if (strnlen(cp->input, SCAN_INPUT_LEN) == 0) {
        ntlang_error("No expression given to evaluate");
        exit(-1);
    }
}
