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
	if(base==2){
		uint32_t mask;
		if(width==32){
			mask = (1 << (width-1)) -1;
		} else{
			mask = (1 << width) -1;
		}
		result = result & mask;
	}
	if(base==16){
			uint32_t mask = (1 << width/4) -1;
			result = result & mask;
	}

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

int generate_output(uint32_t result, char* output, int base, int width){
	int i = 0;
	int denom;
	if(base==2){
		denom = 1;
	} else {
		denom = 4;
	}
	while(i<(width/denom)){
		uint32_t temp = result % base;
		output[i++] = uint32_digit_char(temp);
   	 	result = result / base;
	}

	return i;
	
}


void print_output_in_base2 (uint32_t result, int width) {
	char output[64];
	uint32_t mask;
	if(width==32){
		mask = (1 << (width-1)) -1;
	} else{
		mask = (1 << width) -1;
	}
	result = result & mask;

	int i = generate_output(result, output, 2, width);
	// while(i<width){
		// output[i++] = '0';
	// }
	output[i++] = 'b';
	output[i++] = '0';
	output[i] = '\0';
	reverse(output);
	printf("%s\n", output);
}

void print_output_in_base10 (uint32_t result, int width) {
	char output[64];
	uint32_t mask;
	if(width==32){
		mask = (1 << (width-1)) -1;
	} else{
		mask = (1 << width) -1;
	}
	// printf("Result before mask %d\n", result);
	result = result & mask;
	// printf("Result %d\n", result);
	// printf("Mask %d\n", mask);
	// int i = generate_output(result, output, 10, width);
	int i = 0;
	int base = 10;
	if(result==0){
		output[i++] = '0';
	}
	while(result!=0){
		uint32_t temp = result % base;
		output[i++] = uint32_digit_char(temp);
   	 	result = result / base;
	}
	output[i] = '\0';
	reverse(output);
	printf("%s\n", output);
}

void print_output_in_base16 (uint32_t result, int width) {
	char output[64];
	uint32_t mask;
	if(width==32){
		mask = (1 << (width-1)) -1;
	} else{
		 mask = (1 << width) -1;
	}
	result = result & mask;
	int i = generate_output(result, output, 16, width);
	// while(i<width/4){
		// output[i++] = '0';
	// }
	output[i++] = 'x';
	output[i++] = '0';
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
    if(cp->base==10 && cp->unsigned_flag==true){
    	printf("%d\n", value);
    } else if(cp->base==10) {
      	print_output_in_base10(value, cp->width);
    } else if(cp->base==2) {
    	print_output_in_base2(value, cp->width);
    } else if(cp->base==16) {
       	print_output_in_base16(value, cp->width);
    } else{
   		print_output_in_base(value, cp->base, cp->width);
    }
    //printf("%d\n", value);
}



