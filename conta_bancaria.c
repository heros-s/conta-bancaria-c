#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100

typedef struct {
    char nome[100];
    int idade;
    char cpf[12];
    int tipo_conta; // 0 para conta corrente, 1 para conta poupança
    int status; // 0 para conta fechada, 1 para conta aberta
    float saldo;
} Cliente;

Cliente clientes[MAX_CLIENTES];
int numClientes = 0;
float limite_credito = 0.2; // 20% da soma dos saldos

void abrirConta() {
    if(numClientes >= MAX_CLIENTES)
    {
        printf("maximo de clientes atingido\n");
        return;
    }

    Cliente novoCliente;
    printf("Digite o nome completo: ");
    scanf(" %[^\n]s", novoCliente.nome);
    printf("Digite a idade: ");
    scanf("%d", &novoCliente.idade);
    printf("Digite o CPF: ");
    scanf("%s", novoCliente.cpf);

    // Verificar se o cliente ja esta cadastrado
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, novoCliente.cpf) == 0) {
            printf("Cliente ja cadastrado.\n");
            return;
        }
    }

    // Verificar se o cliente eh maior de idade
    if (novoCliente.idade < 18) {
        printf("Cliente precisa ser maior de idade.\n");
        return;
    }

    // Adicionar cliente na lista
    novoCliente.tipo_conta = -1; // inicializacao
    novoCliente.status = 1; // conta aberta
    novoCliente.saldo = 0;
    clientes[numClientes++] = novoCliente;

    printf("Cliente cadastrado com sucesso.\n");

    // Menu para escolher o tipo de conta
    printf("Escolha o tipo de conta:\n");
    printf("1. Conta Corrente\n");
    printf("2. Conta Poupanca\n");
    int opcao;
    scanf("%d", &opcao);

    if (opcao == 1 || opcao == 2) {
        clientes[numClientes - 1].tipo_conta = opcao - 1; // 0 para conta corrente, 1 para conta poupança
        printf("Conta %s criada com sucesso.\n", opcao == 1 ? "Corrente" : "Poupanca");
        clientes[numClientes - 1].saldo = 0;
    } else {
        printf("Opcao invalida.\n");
    }
}

void listarClientes() {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Tipo de Conta: %s\n", clientes[i].tipo_conta == 0 ? "Corrente" : "Poupança");
        printf("Status: %s\n", clientes[i].status == 1 ? "Aberta" : "Fechada");
        printf("Saldo: R$ %.2f\n", clientes[i].saldo);
        printf("-----------------\n");
    }
}

void fazerDeposito() {
    int numConta;
    float valor;

    printf("Digite o numero da conta: ");
    scanf("%d", &numConta);

    if (numConta >= 1 && numConta <= numClientes) {
        printf("Digite o valor do depósito: ");
        scanf("%f", &valor);

        clientes[numConta - 1].saldo += valor;
        printf("Deposito realizado com sucesso.\n");
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void fazerSaque() {
    int numConta;
    float valor;

    printf("Digite o numero da conta: ");
    scanf("%d", &numConta);

    if (numConta >= 1 && numConta <= numClientes) {
        printf("Digite o valor do saque: ");
        scanf("%f", &valor);

        if (clientes[numConta - 1].saldo >= valor) {
            clientes[numConta - 1].saldo -= valor;
            printf("Saque realizado com sucesso.\n");
        } else {
            printf("Saldo insuficiente.\n");
        }
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void fecharConta() {
    int numConta;

    printf("Digite o numero da conta que deseja fechar: ");
    scanf("%d", &numConta);

    if (numConta >= 1 && numConta <= numClientes) {
        clientes[numConta - 1].status = 0; // conta fechada
        printf("Conta fechada com sucesso.\n");
    } else {
        printf("Conta nao encontrada.\n");
    }
}

void fazerEmprestimo() {
    int numConta;
    float valor;

    printf("Digite o numero da conta: ");
    scanf("%d", &numConta);

    if (numConta >= 1 && numConta <= numClientes) {
        printf("Digite o valor do emprestimo: ");
        scanf("%f", &valor);

        if (valor <= 0) {
            printf("Valor do emprestimo deve ser maior que zero.\n");
            return;
        }

        // Verificar se o cliente tem saldo suficiente para o emprestimo
        float saldo_disponivel = clientes[numConta - 1].saldo + (clientes[numConta - 1].saldo * limite_credito);
        if (valor <= saldo_disponivel) {
            clientes[numConta - 1].saldo += valor;
            printf("Emprestimo de R$ %.2f realizado com sucesso.\n", valor);
        } else {
            printf("Saldo insuficiente para o emprestimo.\n");
        }
    } else {
        printf("Conta nao encontrada.\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal:\n");
        printf("(1) Abrir conta\n");
        printf("(2) Listar clientes\n");
        printf("(3) Fazer deposito\n");
        printf("(4) Fazer saque\n");
        printf("(5) Fechar conta\n");
        printf("(6) Fazer emprestimo\n");
        printf("(0) Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                abrirConta();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                fazerDeposito();
                break;
            case 4:
                fazerSaque();
                break;
            case 5:
                fecharConta();
                break;
            case 6:
                fazerEmprestimo();
                break;
            case 0:
                printf("Saindo do programa. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}