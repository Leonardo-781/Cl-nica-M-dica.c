#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_REGISTROS 30

typedef struct {
    char cpf[12];
    char nome[100];
    char telefone[20];
    char endereco[150];
    char dataNascimento[11];
} Paciente;

typedef struct {
    char nome[100];
    char crm[20];
    int cargaHoraria;
    float salario;
    char especialidade[50];
} Medico;

typedef struct {
    char cpfPaciente[12];
    char crmMedico[20];
    char dataAtendimento[11];
} Atendimento;

Paciente pacientes[MAX_REGISTROS];
int numPacientes = 0;

Medico medicos[MAX_REGISTROS];
int numMedicos = 0;

Atendimento atendimentos[MAX_REGISTROS];
int numAtendimentos = 0;

/////// METODOS

void editarAtendimentoPorCPF();

void editarAtendimentoPorCRM();

void editarAtendimentoSelecionado(int atendimento);

int encontrarIndiceMedicoPorCRM(char* crm) {
    for (int i = 0; i < numMedicos; i++) {
        if (strcmp(medicos[i].crm, crm) == 0) return i;
    }
    return -1;
}

int encontrarIndicePacientePorCPF(char* cpf) {
    for (int i = 0; i < numPacientes; i++) {
        if (strcmp(pacientes[i].cpf, cpf) == 0) return i;
    }
    return -1;
}

int encontrarIndiceAtendimento(char* cpf, char* crm) {
    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].cpfPaciente, cpf) == 0 && strcmp(atendimentos[i].crmMedico, crm) == 0) return i;
    }
    return -1;
}

bool crmExiste(char *crm) {
    return encontrarIndiceMedicoPorCRM(crm) != -1;
}

bool cpfExiste(char *cpf) {
    return encontrarIndicePacientePorCPF(cpf) != -1;
}

bool atendimentoExiste(char *cpf, char *crm, char *data) {
    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].cpfPaciente, cpf) == 0 && strcmp(atendimentos[i].crmMedico, crm) == 0 && strcmp(atendimentos[i].dataAtendimento, data) == 0) return true;
    }
    return false;
}

void cadastrarPaciente() {
    if (numPacientes >= MAX_REGISTROS) {
        printf("Limite de pacientes alcançado.\n");
        return;
    }
    Paciente novoPaciente;
    printf("CPF do paciente: ");
    scanf("%s", novoPaciente.cpf);
    if (cpfExiste(novoPaciente.cpf)) {
        printf("Este CPF já está cadastrado.\n");
        return;
    }
    printf("Nome do paciente: ");
    scanf(" %[^\n]s", novoPaciente.nome);
    printf("Telefone do paciente: ");
    scanf("%s", novoPaciente.telefone);
    printf("Endereço do paciente: ");
    scanf(" %[^\n]s", novoPaciente.endereco);
    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", novoPaciente.dataNascimento);

    pacientes[numPacientes++] = novoPaciente;
    printf("Paciente cadastrado com sucesso.\n");
}

void cadastrarMedico() {
    if (numMedicos >= MAX_REGISTROS) {
        printf("Limite de médicos alcançado.\n");
        return;
    }
    Medico novoMedico;
    printf("CRM do médico: ");
    scanf("%s", novoMedico.crm);
    if (crmExiste(novoMedico.crm)) {
        printf("Este CRM já está cadastrado.\n");
        return;
    }
    printf("Nome do médico: ");
    scanf(" %[^\n]s", novoMedico.nome);
    printf("Carga horária: ");
    scanf("%d", &novoMedico.cargaHoraria);
    printf("Salário: ");
    scanf("%f", &novoMedico.salario);
    printf("Especialidade: ");
    scanf(" %[^\n]s", novoMedico.especialidade);

    medicos[numMedicos++] = novoMedico;
    printf("Médico cadastrado com sucesso.\n");
}

void cadastrarAtendimento() {
    if (numAtendimentos >= MAX_REGISTROS) {
        printf("Limite de atendimentos alcançado.\n");
        return;
    }
    Atendimento novoAtendimento;
    printf("CPF do paciente: ");
    scanf("%s", novoAtendimento.cpfPaciente);
    if (!cpfExiste(novoAtendimento.cpfPaciente)) {
        printf("CPF do paciente não encontrado.\n");
        return;
    }
    printf("CRM do médico: ");
    scanf("%s", novoAtendimento.crmMedico);
    if (!crmExiste(novoAtendimento.crmMedico)) {
        printf("CRM do médico não encontrado.\n");
        return;
    }
    printf("Data do atendimento (DD/MM/AAAA): ");
    scanf("%s", novoAtendimento.dataAtendimento);
    if (atendimentoExiste(novoAtendimento.cpfPaciente, novoAtendimento.crmMedico, novoAtendimento.dataAtendimento)) {
        printf("Atendimento já cadastrado para esta data.\n");
        return;
    }

    atendimentos[numAtendimentos++] = novoAtendimento;
    printf("Atendimento cadastrado com sucesso.\n");
}

void editarPaciente() {
    char cpf[12];
    printf("Digite o CPF do paciente para editar: ");
    scanf("%s", cpf);
    int indice = encontrarIndicePacientePorCPF(cpf);
    if (indice == -1) {
        printf("Paciente não encontrado.\n");
        return;
    }

    printf("Editar nome (anterior: %s): ", pacientes[indice].nome);
    scanf(" %[^\n]s", pacientes[indice].nome);
    printf("Editar telefone (anterior: %s): ", pacientes[indice].telefone);
    scanf("%s", pacientes[indice].telefone);
    printf("Editar endereço (anterior: %s): ", pacientes[indice].endereco);
    scanf(" %[^\n]s", pacientes[indice].endereco);
    printf("Editar data de nascimento (DD/MM/AAAA, anterior: %s): ", pacientes[indice].dataNascimento);
    scanf("%s", pacientes[indice].dataNascimento);

    printf("Paciente atualizado com sucesso.\n");
}


void editarMedico() {
    char crm[20];
    printf("Digite o CRM do médico para editar: ");
    scanf("%s", crm);
    int indice = encontrarIndiceMedicoPorCRM(crm);
    if (indice == -1) {
        printf("Médico não encontrado.\n");
        return;
    }

    printf("Editar nome (anterior: %s): ", medicos[indice].nome);
    scanf(" %[^\n]s", medicos[indice].nome);
    printf("Editar carga horária (anterior: %d): ", medicos[indice].cargaHoraria);
    scanf("%d", &medicos[indice].cargaHoraria);
    printf("Editar salário (anterior: %.2f): ", medicos[indice].salario);
    scanf("%f", &medicos[indice].salario);
    printf("Editar especialidade (anterior: %s): ", medicos[indice].especialidade);
    scanf(" %[^\n]s", medicos[indice].especialidade);

    printf("Médico atualizado com sucesso.\n");
}

void escolherAtendimentoParaEdicao(void) {
    int escolha;
    printf("Buscar atendimento por:\n1. CPF do Paciente\n2. CRM do Médico\nEscolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            editarAtendimentoPorCPF();
            break;
        case 2:
            editarAtendimentoPorCRM();
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void editarAtendimentoPorCRM() {
    char crm[20];
    printf("Digite o CRM do médico: ");
    scanf("%s", crm);
    printf("Atendimentos para o CRM %s:\n", crm);
    bool encontrado = false;
    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].crmMedico, crm) == 0) {
            printf("%d. Paciente: %s, Data: %s\n", i, atendimentos[i].cpfPaciente, atendimentos[i].dataAtendimento);
            encontrado = true;
        }
    }
    if (!encontrado) {
        printf("Nenhum atendimento encontrado para este CRM.\n");
        return;
    }

    int escolhaAtendimento;
    printf("Digite o número do atendimento para editar: ");
    scanf("%d", &escolhaAtendimento);

    if (escolhaAtendimento >= 0 && escolhaAtendimento < numAtendimentos && strcmp(atendimentos[escolhaAtendimento].crmMedico, crm) == 0) {
        editarAtendimentoSelecionado(escolhaAtendimento);
    } else {
        printf("Escolha inválida.\n");
    }
}

void editarAtendimentoPorCPF() {
    char cpf[12];
    printf("Digite o CPF do paciente: ");
    scanf("%s", cpf);
    printf("Atendimentos para o CPF %s:\n", cpf);
    bool encontrado = false;
    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].cpfPaciente, cpf) == 0) {
            printf("%d. Médico: %s, Data: %s\n", i, atendimentos[i].crmMedico, atendimentos[i].dataAtendimento);
            encontrado = true;
        }
    }
    if (!encontrado) {
        printf("Nenhum atendimento encontrado para este CPF.\n");
        return;
    }

    int escolhaAtendimento;
    printf("Digite o número do atendimento para editar: ");
    scanf("%d", &escolhaAtendimento);

    if (escolhaAtendimento >= 0 && escolhaAtendimento < numAtendimentos && strcmp(atendimentos[escolhaAtendimento].cpfPaciente, cpf) == 0) {
        editarAtendimentoSelecionado(escolhaAtendimento);
    } else {
        printf("Escolha inválida.\n");
    }
}

void editarAtendimentoSelecionado(int atendimento) {
    int escolha;
    printf("Editar:\n1. Médico\n2. Paciente\n3. Data\nEscolha: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("Novo CRM do médico: ");
            scanf("%s", atendimentos[atendimento].crmMedico);
            break;
        case 2:
            printf("Novo CPF do paciente: ");
            scanf("%s", atendimentos[atendimento].cpfPaciente);
            break;
        case 3:
            printf("Nova data (DD/MM/AAAA): ");
            scanf("%s", atendimentos[atendimento].dataAtendimento);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
    printf("Atendimento atualizado com sucesso.\n");
}


void excluirPaciente() {
    char cpf[12];
    printf("CPF do paciente para excluir: ");
    scanf("%s", cpf);

    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].cpfPaciente, cpf) == 0) {
            printf("Não é possível excluir o paciente, pois está em um atendimento.\n");
            return;
        }
    }

    int indice = encontrarIndicePacientePorCPF(cpf);
    if (indice == -1) {
        printf("Paciente não encontrado.\n");
        return;
    }
    for (int i = indice; i < numPacientes - 1; i++) {
        pacientes[i] = pacientes[i + 1];
    }
    numPacientes--;
    printf("Paciente excluído com sucesso.\n");
}


void excluirMedico() {
    char crm[20];
    printf("CRM do médico para excluir: ");
    scanf("%s", crm);

    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].crmMedico, crm) == 0) {
            printf("Não é possível excluir o médico, pois está em um atendimento.\n");
            return;
        }
    }

    int indice = encontrarIndiceMedicoPorCRM(crm);
    if (indice == -1) {
        printf("Médico não encontrado.\n");
        return;
    }
    for (int i = indice; i < numMedicos - 1; i++) {
        medicos[i] = medicos[i + 1];
    }
    numMedicos--;
    printf("Médico excluído com sucesso.\n");
}


void excluirAtendimento() {
    char cpf[12], crm[20];
    printf("Digite o CPF do paciente do atendimento a ser excluido: ");
    scanf("%s", cpf);
    printf("Digite o CRM do médico do atendimento a ser excluido: ");
    scanf("%s", crm);
    int indice = encontrarIndiceAtendimento(cpf, crm);
    if (indice == -1) {
        printf("Atendimento não encontrado.\n");
        return;
    }
    for (int i = indice; i < numAtendimentos - 1; i++) {
        atendimentos[i] = atendimentos[i + 1];
    }
    numAtendimentos--;
    printf("Atendimento excluído com sucesso.\n");
}

void salvarDados() {
    FILE *fp = fopen("pacientes.txt", "w");
    for (int i = 0; i < numPacientes; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s\n",
                pacientes[i].cpf, pacientes[i].nome,
                pacientes[i].telefone, pacientes[i].endereco,
                pacientes[i].dataNascimento);
    }
    fclose(fp);

    fp = fopen("medicos.txt", "w");
    for (int i = 0; i < numMedicos; i++) {
        fprintf(fp, "%s,%s,%d,%f,%s\n",
                medicos[i].crm, medicos[i].nome,
                medicos[i].cargaHoraria, medicos[i].salario,
                medicos[i].especialidade);
    }
    fclose(fp);

    fp = fopen("atendimentos.txt", "w");
    for (int i = 0; i < numAtendimentos; i++) {
        fprintf(fp, "%s,%s,%s\n",
                atendimentos[i].cpfPaciente, atendimentos[i].crmMedico,
                atendimentos[i].dataAtendimento);
    }
    fclose(fp);
}

void carregarDados() {
    FILE *fp = fopen("pacientes.txt", "r");
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%s\n",
                  pacientes[numPacientes].cpf, pacientes[numPacientes].nome,
                  pacientes[numPacientes].telefone, pacientes[numPacientes].endereco,
                  pacientes[numPacientes].dataNascimento) != EOF) {
        numPacientes++;
    }
    fclose(fp);

    fp = fopen("medicos.txt", "r");
    while (fscanf(fp, "%[^,],%[^,],%d,%f,%s\n",
                  medicos[numMedicos].crm, medicos[numMedicos].nome,
                  &medicos[numMedicos].cargaHoraria, &medicos[numMedicos].salario,
                  medicos[numMedicos].especialidade) != EOF) {
        numMedicos++;
    }
    fclose(fp);

    fp = fopen("atendimentos.txt", "r");
    while (fscanf(fp, "%[^,],%[^,],%s\n",
                  atendimentos[numAtendimentos].cpfPaciente, atendimentos[numAtendimentos].crmMedico,
                  atendimentos[numAtendimentos].dataAtendimento) != EOF) {
        numAtendimentos++;
    }
    fclose(fp);
}

void listarMedicos() {
    printf("Médicos cadastrados:\n");
    for (int i = 0; i < numMedicos; i++) {
        printf("CRM: %s, Nome: %s, Especialidade: %s, Carga Horária: %d, Salário: %.2f\n",
               medicos[i].crm, medicos[i].nome, medicos[i].especialidade,
               medicos[i].cargaHoraria, medicos[i].salario);
    }
}

void listarPacientes() {
    printf("Pacientes cadastrados:\n");
    for (int i = 0; i < numPacientes; i++) {
        printf("CPF: %s, Nome: %s, Telefone: %s, Endereço: %s, Data de Nascimento: %s\n",
               pacientes[i].cpf, pacientes[i].nome, pacientes[i].telefone,
               pacientes[i].endereco, pacientes[i].dataNascimento);
    }
}

void mostrarAtendimentosPacientePorNome() {
    char nomePaciente[100];
    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]s", nomePaciente);
    bool encontrado = false;

    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(pacientes[encontrarIndicePacientePorCPF(atendimentos[i].cpfPaciente)].nome, nomePaciente) == 0) {
            printf("Atendimento: Médico %s, CRM: %s, Data: %s\n",
                   medicos[encontrarIndiceMedicoPorCRM(atendimentos[i].crmMedico)].nome,
                   atendimentos[i].crmMedico, atendimentos[i].dataAtendimento);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Nenhum atendimento encontrado para este paciente.\n");
    }
}


void gerarRelatorioAtendimentosPeriodo() {
    char dataInicio[11];
    printf("Digite a data de início (DD/MM/AAAA): ");
    scanf("%s", dataInicio);

    char dataAtual[11] = "31/12/2024";

    FILE *fp = fopen("relatorio_atendimentos.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de relatório.\n");
        return;
    }

    for (int i = 0; i < numAtendimentos; i++) {
        if (strcmp(atendimentos[i].dataAtendimento, dataInicio) >= 0 &&
            strcmp(atendimentos[i].dataAtendimento, dataAtual) <= 0) {
            fprintf(fp, "CRM: %s, Médico: %s, CPF: %s, Paciente: %s, Data: %s\n",
                    atendimentos[i].crmMedico,
                    medicos[encontrarIndiceMedicoPorCRM(atendimentos[i].crmMedico)].nome,
                    atendimentos[i].cpfPaciente,
                    pacientes[encontrarIndicePacientePorCPF(atendimentos[i].cpfPaciente)].nome,
                    atendimentos[i].dataAtendimento);
        }
    }

    fclose(fp);
    printf("Relatório de atendimentos gerado com sucesso.\n");
}

///// MAIN

int main() {
    carregarDados();

    int escolha;
    do {
        printf("\n========================================\n");
        printf("          Clínica Médica - Menu\n");
        printf("========================================\n");
        printf("[1]  Cadastrar Paciente\n");
        printf("[2]  Editar Paciente\n");
        printf("[3]  Excluir Paciente\n");
        printf("----------------------------------------\n");
        printf("[4]  Cadastrar Médico\n");
        printf("[5]  Editar Médico\n");
        printf("[6]  Excluir Médico\n");
        printf("----------------------------------------\n");
        printf("[7]  Cadastrar Atendimento\n");
        printf("[8]  Editar Atendimento\n");
        printf("[9]  Excluir Atendimento\n");
        printf("----------------------------------------\n");
        printf("[10] Listar Médicos\n");
        printf("[11] Listar Pacientes\n");
        printf("[12] Mostrar Atendimentos por Nome do Paciente\n");
        printf("[13] Gerar Relatório de Atendimentos por Período\n");
        printf("----------------------------------------\n");
        printf("[14] Salvar Dados e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: cadastrarPaciente(); break;
            case 2: editarPaciente(); break;
            case 3: excluirPaciente(); break;
            case 4: cadastrarMedico(); break;
            case 5: editarMedico(); break;
            case 6: excluirMedico(); break;
            case 7: cadastrarAtendimento(); break;
            case 8: escolherAtendimentoParaEdicao(); break;
            case 9: excluirAtendimento(); break;
            case 10: listarMedicos(); break;
            case 11: listarPacientes(); break;
            case 12: mostrarAtendimentosPacientePorNome(); break;
            case 13: gerarRelatorioAtendimentosPeriodo(); break;
            case 14: salvarDados(); printf("Dados salvos. Saindo...\n"); return 0;
            default: printf("Opção inválida!\n");
        }
    } while (escolha != 14);

    return 0;
}
