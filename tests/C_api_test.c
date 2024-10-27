#include <salamapper/salamapper.h>
#include <assert.h>
#include <stdio.h>

void BasicTest(){
	const char* input = "1:2,3,5;2:3;3:4;4:;5:6,7;6:7;7:;";
	const char* root_id = "1";

	TreeHandle* tree = CreateTree(input, root_id, CYCLE_IGNORE);
	assert(tree != NULL && "Tree Creation Failed");

	char* ASCII_Output = GetTree(tree);
	assert(ASCII_Output != NULL && "ASCII_Output Failed");
	printf("Tree visualization: \n%s\n", ASCII_Output);

	FreeString(ASCII_Output);
	ClearTree(tree);
	printf("Basic functionality test passed\n");
}

void ErrorHandlingTest(){
	TreeHandle *tree = CreateTree("invalid format", "1", CYCLE_IGNORE);
	assert(tree == NULL && "Invalid input handling failed");

	tree = CreateTree(NULL, "1", CYCLE_IGNORE);
	assert(tree == NULL && "Null input handling failed");

	char* format = "1:2;2:1";
	tree = CreateTree(format, "1", CYCLE_ERROR);
	assert(tree == NULL && "Cycle Error undetected");

	tree = CreateTree(format, "1", CYCLE_IGNORE);
	assert(tree != NULL && "Cycle Error detected when using ignore");

	format = "1:2;2:3,4;3:1,4;4:";
	tree = CreateTree(format, "1", CYCLE_ERROR);
	assert(tree == NULL && "Cycle Error undetected");
	
	tree = CreateTree(format, "1", CYCLE_IGNORE);
	assert(tree != NULL && "Cycle Error detected when using ignore");

	printf("Error handling test passed\n");
}

void TopSortTest(){
	const char* format = "1:2,3,4;2:5,6,7;3:8,9;4:10,11,12;5:13,146;6:15,16,17;7:18;8:19,20;9:21,22,23;10:24,25;11:26,27,28;12:29;13:30,31;14:32,33,34;15:35;16:36,37;17:38,39,40;18:41,42;19:43,44;20:45;21:46,47,48;22:49;23:50,51;24:52,53,54;25:55;26:56,57;27:58,59,60;28:61;29:62,63;30:64,65;31:66;32:67,68,69;33:70;34:71,72;35:73,74,75;36:76;37:77,78;38:79,80,81;39:82;40:83,84;41:85,86;42:87;43:88,89,90;44:91;45:92,93;46:94,95,96;47:97;48:98,99;49:100;50:101,102,103;51:104;52:105,106;53:107,108,109;54:110;55:111,112;56:113,114,115;57:116;58:117,118;59:119,120,121;60:122;61:123,124;62:125,126,127;63:128;64:129,130;65:131,132,133;66:134;67:135,136;68:137,138,139;69:140;70:141,142;71:143,144,145;72:146;73:147,148;74:149,150,151;75:152;76:153,154;77:155,156,157;78:158;79:159,160;80:161,162,163;81:164;82:165,166;83:167,168,169;84:170;85:171,172;86:173,174,175;87:176;88:177,178;89:179,180,181;90:182;91:183,184;92:185,186,187;93:188;94:189,190;95:191,192,193;96:194;97:195,196;98:197,198,199;99:200;100:;101:;102:;103:;104:;105:;106:;107:;108:;109:;110:;111:;112:;113:;114:;115:;116:;117:;118:;119:;120:;121:;122:;123:;124:;125:;126:;127:;128:;129:;130:;131:;132:;133:;134:;135:;136:;137:;138:;139:;140:;141:;142:;143:;144:;145:;146:;147:;148:;149:;150:;151:;152:;153:;154:;155:;156:;157:;158:;159:;160:;161:;162:;163:;164:;165:;166:;167:;168:;169:;170:;171:;172:;173:;174:;175:;176:;177:;178:;179:;180:;181:;182:;183:;184:;185:;186:;187:;188:;189:;190:;191:;192:;193:;194:;195:;196:;197:;198:;199:;200:;";
	const char* root_id = "1";
	char* kahn = TopSortKahnString(format);
	assert(kahn != NULL && "Kahn C api failed");
	printf("Topological order: %s\n", kahn);

	TreeHandle* tree = CreateTree(format, root_id, CYCLE_ERROR); 
	kahn = TopSortKahnHandle(tree);
	assert(kahn != NULL && "Kahn C api failed");
	printf("Topological order: %s\n", kahn);	

	printf("Topological test passed\n");	
}

int main(){
	printf("Starting salamapper C API test... \n");

	BasicTest();
	ErrorHandlingTest();
	TopSortTest();

	printf("All test completed succesfully\n");
	return 0;
}