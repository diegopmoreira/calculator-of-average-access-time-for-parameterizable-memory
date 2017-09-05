#include "tm.h"
#include "simpletest.h"


void teste_so_mem(){
	WHEN("Testando só memória principal");

	IF("Somente a memória principal é usada");
	THEN("O tempo médio tem que ser igual ao da memória");

	isEqualUint32(tempo_medio(0,0,0,0,0,0,100), 100, 1);

	IF("O primeiro nível é zero");
	THEN("Devem ser desconsiderados L2 e L3");
	
	isEqualUint32(tempo_medio(0,1,2,3,4,5,100), 100, 1);

	IF("O tempo de acesso da memória é zero");
	THEN("Média deve ser zero");
	isEqualUint32(tempo_medio(0,0,0,0,0,0,0), 0, 1);
}


void teste_l1(){
	WHEN("Testando o primeiro nível de memória");

	IF("Taxa de miss é 100\%");
	THEN("Média vai ser 101");

	isEqualUint32(tempo_medio(1,100000,0,0,0,0,100), 101, 1);

	IF("Taxa de miss é muito baixa, 5 por 100K");
	THEN("Média vai ser valor da L1 mais uma fração");

	isEqualUint32(tempo_medio(1,5,0,0,0,0,100), 2, 1);

	IF("Taxa de miss é 50\%");
	THEN("Média será 51");

	isEqualUint32(tempo_medio(1,50000,0,0,0,0,100), 51, 1);

	IF("Taxa de miss é 1\%");
	THEN("Média será 2");

	isEqualUint32(tempo_medio(1,1000,0,0,0,0,100), 2, 1);

}

void teste_l2(){
	WHEN("Testando o segundo nível de memória");

	IF("Tempo de acesso é zero");
	THEN("Média vai ignorar o nível");
	isEqualUint32(tempo_medio(1,1000,0,10000,0,0,100), 2, 1);

	WHEN("Miss na L1 é 1\%");
	IF("Taxa de miss é 5\%");
	THEN("Média será 2");
	isEqualUint32(tempo_medio(1,1000,10,5000,0,0,100), 2, 1);

	IF("Taxa de miss é 10\%");
	THEN("Média será 2");
	isEqualUint32(tempo_medio(1,1000,10,10000,0,0,100), 2, 1);

	WHEN("Miss na L1 é 5%");
	IF("Taxa de miss é 5\%");
	THEN("Média será 2");
	isEqualUint32(tempo_medio(1,5000,10,5000,0,0,100), 2, 1);

	IF("Taxa de miss é 10\%");
	THEN("Média será 2");
	isEqualUint32(tempo_medio(1,1000,10,10000,0,0,100), 2, 1);

	IF("Taxa de miss é 15\%");
	THEN("Média será 3");
	isEqualUint32(tempo_medio(1,1000,10,15000,0,0,100), 2, 1);

	WHEN("Aumenta-se a taxa de miss na L1 para 20\%");
	IF("Taxa de miss é 15\%");
	THEN("Média será 6");
	isEqualUint32(tempo_medio(1,20000,10,15000,0,0,100), 6, 1);

}


void teste_l3(){
	WHEN("Testando o terceiro nível de memória");


	WHEN("Miss na L1 é 5\% e na L2, 10\%");
	IF("Taxa de miss é 5\%");
	THEN("Média será 2");
	isEqualUint32(tempo_medio(1,5000,10,10000,20,5000,100), 2, 5);

	IF("Taxa de miss é 90\%");
	THEN("Média será 3");
	isEqualUint32(tempo_medio(1,5000,10,10000,20,90000,100), 3, 5);

	WHEN("Miss na L1 é 10\% e na L2, 15\%");
	IF("Taxa de miss é 95\%");
	THEN("Média será 4");
	isEqualUint32(tempo_medio(1,10000,10,15000,20,95000,100), 4, 5);

	WHEN("Tempo de acesso na L1 é 2ns, miss na L1 é 10\% e na L2, 15\%");
	IF("Taxa de miss é 95\%");
	THEN("Média será 5");
	isEqualUint32(tempo_medio(2,10000,10,15000,20,95000,100), 5, 5);

}


int main(int argc, char ** argv){

	DESCRIBE("Teste da calculadora de tempo médio de acesso a hierarquia de memória");

	teste_so_mem();
	teste_l1();
	teste_l2();
	teste_l3();

	GRADEME();

	if (grade==maxgrade)
		return 0;
	else return grade;

}
