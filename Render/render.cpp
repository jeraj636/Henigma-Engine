#include "render.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Okno::Okno()
    : _barvaOdzadja(0x00ffffff)
{
}
void Okno::nastavi(int dolzinaOkna, int VisinaOkna, const char *naslovOkna)
{
    if (!glfwInit())
        io::izpis("NI GLFWJA", io::type::error);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    okno = glfwCreateWindow(dolzinaOkna, VisinaOkna, naslovOkna, NULL, NULL);
    if (okno == NULL)
        io::izpis("NI OKNA", io::type::error);

    glfwMakeContextCurrent(okno);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        io::izpis("NI GLADA", io::type::error);
    glfwSetFramebufferSizeCallback(okno, posodobiVelikostOkna);

    float tocke[] =
        {
            1.0, 1.0, 0.0, 1, 1,
            1.0, -1.0, 0.0, 1, 0,
            -1.0, -1.0, 0.0, 0, 0,
            -1.0, 1.0, 0.0, 0, 1};
    int indeksi[] =
        {
            0, 1, 2,
            0, 2, 3};

    const char *vertexShaderS = R"(
            #version 330 core
            layout (location=0) in vec3 aPos;
            layout (location=1)in vec2 atexCor;
            out vec2 texCor;
            uniform mat4 matrica;
            void main()
            {
                gl_Position=matrica *vec4(aPos,1);
                texCor=atexCor;
            }
        )";
    const char *fragmentShaderS = R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec4 barva;
            uniform sampler2D teks;
            in vec2 texCor;
            void main() 
            {
               // FragColor = vec4(barva);
               FragColor=texture(teks,texCor)*vec4(barva);
            } 

        )";
    //*zacetek testure

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int visina, sirina, barvnoKodiranje;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../images.png", &visina, &sirina, &barvnoKodiranje, 0);
    if (data == nullptr)
        io::izpis("ni ok", io::type::msg);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, visina, sirina, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //*konec s teksturami
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksi), indeksi, GL_STATIC_DRAW);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke), tocke, GL_STATIC_DRAW);

    int uspeh;
    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexShader, 1, &vertexShaderS, NULL);
    glCompileShader(_vertexShader);
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI VERTEX SHADERJA", io::type::msg);

    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShader, 1, &fragmentShaderS, NULL);
    glCompileShader(_fragmentShader);
    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI FRGAMENT SHADERJA", io::type::msg);

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertexShader);
    glAttachShader(_shaderProgram, _fragmentShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
        io::izpis("NI PROGRAMA", io::type::error);

    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
}
void Okno::spremeniBarvo(Barva barva)
{
    _barvaOdzadja = barva;
}
void Okno::dodajSceno(const std::string &imeScene)
{
    tabScen.push_back(new Scena(imeScene));
    tabScen.back()->nastavi(this);
}
Scena *Okno::poisciSceno(const std::string &imeScene)
{
    for (int i = 0; i < tabScen.size(); i++)
    {
        if (imeScene == tabScen[i]->ime)
            return tabScen[i];
    }
    return nullptr;
}
void Okno::zanka()
{
    glClearColor(_barvaOdzadja.r, _barvaOdzadja.g, _barvaOdzadja.b, _barvaOdzadja.a);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < tabScen.size(); i++)
    {
        tabScen[i]->zanka();
    }
    glfwSwapBuffers(okno);
}
// GLFWwindow *Okno::okno = 0;
Okno::~Okno()
{
    glfwTerminate();
}
void Okno::unici(Scena *kateraScena)
{
    delete kateraScena;
}
// std::vector<Objekt *> tabObjektov;
//  Barva Okno::_barvaOdzadja;
/*static void posodobiVelikostOkna(GLFWwindow *okno, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}*/
static uint _VBO;
static uint _VAO;
static uint _EBO;
static uint _vertexShader;
static uint _fragmentShader;
static uint _shaderProgram;
static uint _texture;
uint Okno::_VBO = 0;
uint Okno::_VAO = 0;
uint Okno::_EBO = 0;
uint Okno::_vertexShader = 0;
uint Okno::_fragmentShader = 0;
uint Okno::_shaderProgram = 0;
uint Okno::_texture = 0;
