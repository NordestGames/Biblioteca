typedef struct Livros Livros;
struct no;
struct usuario;
int emailValido(const char *email);
int emailVerifica(const char *email);
void registrarUsuario();
int loginUser();
typedef struct no No;
typedef struct Lista Lista;
void adicionaFim(Lista *lista, Livros e);
void mostrar(Lista lista);
void editarValor(Lista* lista, int id, float valor);
void deletar(Lista *lista, int id);
void ler(Livros *e);
void telaInicial();
void menu();
void cadastrar();
void buscar (int id);
void listar();
int tamanho();
void lerLista(Lista *lista);
void salvaLista(Lista *lista);
void excluir(int id);
void editar(int id);