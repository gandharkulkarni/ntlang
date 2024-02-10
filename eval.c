/* eval.c - tree evaluation and value printing */

#include "ntlang.h"

void eval_error(char *err) {
    printf("eval_error: %s\n", err);
    exit(-1);
}

uint32_t eval(struct parse_node_st *pt) {
    uint32_t v1, v2;

    if (pt->type == EX_INTVAL) {
        v1 = pt->intval.value;
    } else if (pt->type == EX_OPER1) {
        v1 = eval(pt->oper1.operand);
        if (pt->oper1.oper == OP_MINUS) {
            v1 = -v1;
        } else if (pt->oper1.oper == OP_NOT) {
            v1 = ~v1;
        } else {
       		eval_error("Bad operator");
        }
    } else if (pt->type == EX_OPER2) {
        v1 = eval(pt->oper2.left);
        v2 = eval(pt->oper2.right);
        if (pt->oper2.oper == OP_PLUS) {
            v1 = v1 + v2;
        } else if (pt->oper2.oper == OP_MINUS) {
            v1 = v1 - v2;
        } else if (pt->oper2.oper == OP_MULT) {
            v1 = v1 * v2;
        } else if (pt->oper2.oper == OP_DIV) {
        	if(v2 != 0) {
        		v1 = v1 / v2;	
        	} else{
        		eval_error("Division by zero"); 
        	}
        } else if (pt->oper2.oper == OP_LSR) {
            v1 = v1 >> v2;
        } else if (pt->oper2.oper == OP_ASR) {
            v1 = v1 >> v2;
        } else if (pt->oper2.oper == OP_LSL) {
            v1 = v1 << v2;
        } else if (pt->oper2.oper == OP_AND) {
            v1 = v1 & v2;
        } else if (pt->oper2.oper == OP_OR) {
            v1 = v1 | v2;
        } else if (pt->oper2.oper == OP_XOR) {
            v1 = v1 ^ v2;
        } else {
            eval_error("Bad operator");            
        }
    }

    return v1;
}

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void print_output_in_base (uint32_t result, int base, int width) {
	int i=0;
	char output[64];

	uint32_t mask = (width << 1) -1;

	result = result & mask;
	
	while(result!=0){
		uint32_t temp = result % base;
		if(temp<10){
        	output[i++] = '0' + temp;
        } else{
        	output[i++] = 'A' + temp - 10;
        }
        result = result / base;
	}
	int limit = width;
	if (base==16) {
		limit = limit / 4;
	}

	while(i<limit){
		output[i++] = '0';
	}
	if(base==2){
		output[i++] = 'b';
		output[i++] = '0';
	}
	if(base==16){
		output[i++] = 'x';
		output[i++] = '0';
	}
	
	output[i] = '\0';
	reverse(output);
	printf("%s\n", output);
}

void eval_print(struct config_st *cp, uint32_t value) {
    /*
     * Handle -b -w -u
     *
     * Use your own conversion functions for uint32_t to string.
     */
     // printf("Base  %d\n", cp->base);
     // printf("Width %d \n", cp->width);
     // printf("Unsigned flag %d\n", cp->unsigned_flag);
    if(cp->base==10){
    	printf("%d\n", value);
    } else{
   		print_output_in_base(value, cp->base, cp->width);
    }
    //printf("%d\n", value);
}



