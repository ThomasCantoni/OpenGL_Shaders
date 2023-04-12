#include <string>

typedef struct GLFWwindow;
class OGLWindow
{
    
    public:

    OGLWindow(int width,int height,const std::string& InTitle);
    ~OGLWindow();
    void PrintInfo();
    bool IsOpened();
    float GetDeltaTime();
    void Update();
    void SetTitle(const std::string& title);

    private:
    int width,height;
    std::string Title;
    GLFWwindow* RawWindow;
    float DeltaTime=0,LastTime=0;
};