//#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<map>
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

//请用如下函数初始化矩阵 glm::mat4 mat = glm::mat4(1.0f)

float nowmix = 0.4f;
float screenWidth = 960;
float screenHeight = 800;;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
Camera camera;
bool bloom = true;
bool bloomKeyPressed = false;
float exposure = 1.0f;
void Find() {
    GLenum error;
    while ((error = glGetError()) != 0) {
        std::cout << error << std::endl;
    }


}
void Key_Back(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)camera.isQuicked = true;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)camera.isQuicked = false;
    camera.DealMove(window);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    camera.DealRotate(window, xpos, ypos);
}
void RenderScene(Shader &shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0));
    model = glm::scale(model,glm::vec3(10.0f, 0.5f, 10.0f));
    shader.SetUniformMatrix4fv("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void RenderCube(VertexArray &cubeVAO)
{
    cubeVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    cubeVAO.UnBind();
}
void RenderQuad(VertexArray& quadVAO)
{
    quadVAO.Bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    quadVAO.UnBind();
}
int main(void)
{



    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth,screenHeight , "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)std::cout << "error" << std::endl;
    //使用此函数需要先创建OpenGL上下文,不然会返回错误

    

    std::cout << glGetString(GL_VERSION) << std::endl;
    {


        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);

        std::string filePathV = "Res/Shader/BaseV.vt";
        std::string filePathF = "Res/Shader/BaseF.fr";
        std::string FrameShaderPathV = "Res/Shader/HdrShader.vt";
        std::string FrameShaderPathF = "Res/Shader/HdrShader.fr";
        std::string LightPathV = "Res/Shader/LightV.vt";
        std::string LightPathF = "Res/Shader/LightF.fr";
        std::string BlurPathV = "Res/Shader/GaussianBlur.vt";
        std::string BlurPathF = "Res/Shader/GaussianBlur.fr";
        Shader ObjectS(filePathV,filePathF);
        Shader TestShader(FrameShaderPathV, FrameShaderPathF);
        Shader shaderLight(LightPathV, LightPathF);
        Shader shaderBlur(BlurPathV, BlurPathF);
        Texture Container("Res/Texture/container2.png",true);

        // positions
        std::vector<glm::vec3> lightPositions;
        lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
        lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
        lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
        lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
        // colors
        std::vector<glm::vec3> lightColors;
        lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
        lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
        lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
        lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));




        glEnable(GL_DEPTH_TEST);


        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        GLfloat vertices[] = {
                // back face
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
                 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
                // front face
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
                 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                // left face
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                // right face
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
                 // bottom face
                 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
                  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                 -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                 // top face
                 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                  1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
                  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        VertexBuffer cubeVBO;
        VertexArray cubeVAO;
        cubeVAO.Bind();
        cubeVBO.Bind();
        cubeVBO.offerData(sizeof(vertices), vertices, GL_STATIC_DRAW);
        BufferLayout bl;
        bl.Push<float>(3);
        bl.Push<float>(3);
        bl.Push<float>(2);
        cubeVAO.layout = bl;
        cubeVAO.ApplyLayout();
        cubeVBO.UnBind();
        cubeVAO.UnBind();

        VertexBuffer quadVBO;
        VertexArray quadVAO;
        quadVBO.Bind();
        quadVAO.Bind();
        quadVBO.offerData(sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        BufferLayout QBL;
        QBL.Push<float>(3);
        QBL.Push<float>(2);
        quadVAO.layout = QBL;
        quadVAO.ApplyLayout();
        quadVAO.UnBind();
        quadVBO.UnBind();

        //Set up floating point framebuffer to render scene to
        GLuint hdrFBO;
        glGenFramebuffers(1, &hdrFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        GLuint colorBuffers[2];
        glGenTextures(2, colorBuffers);
        for (GLuint i = 0; i < 2; i++)
        {
            glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            // attach texture to framebuffer
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
            );
        }
        GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        GLuint pingpongFBO[2];
        GLuint pingpongColorbuffers[2];
        glGenFramebuffers(2, pingpongFBO);
        glGenTextures(2, pingpongColorbuffers);
        for (GLuint i = 0; i < 2; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0
            );
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);



        ObjectS.Use();
        ObjectS.SetUniform1i("containerTex", 0);
        shaderBlur.Use();
        shaderBlur.SetUniform1i("image", 0);
        TestShader.Use();
        TestShader.SetUniform1i("scene", 0);
        TestShader.SetUniform1i("bloomBlur", 1);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {


            glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 projection = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            view = camera.LookAt();
            projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);

            ObjectS.Use();
            ObjectS.SetUniformMatrix4fv("projection", projection);
            ObjectS.SetUniformMatrix4fv("view", view);
            for (unsigned int i = 0; i < lightPositions.size(); i++)
            {
                ObjectS.SetUniformVector3fv("lights[" + std::to_string(i) + "].position", lightPositions[i]);
                ObjectS.SetUniformVector3fv("lights[" + std::to_string(i) + "].diffuse", lightColors[i]);
            }
            ObjectS.SetUniform1i("inverse_normals", false);
            Container.EnableTexture(1, 0);
            ObjectS.SetUniformVector3fv("viewPos", camera.cameraPos);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
            model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
            model = glm::scale(model, glm::vec3(0.5f));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
            model = glm::scale(model, glm::vec3(0.5f));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
            model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
            model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            model = glm::scale(model, glm::vec3(1.25));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
            model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
            model = glm::scale(model, glm::vec3(0.5f));
            ObjectS.SetUniformMatrix4fv("model", model);
            RenderCube(cubeVAO);



            // finally show all the light sources as bright cubes
            shaderLight.Use();
            shaderLight.SetUniformMatrix4fv("projection", projection);
            shaderLight.SetUniformMatrix4fv("view", view);

            for (unsigned int i = 0; i < lightPositions.size(); i++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(lightPositions[i]));
                model = glm::scale(model, glm::vec3(0.25f));
                shaderLight.SetUniformMatrix4fv("model", model);
                shaderLight.SetUniformVector3fv("lightColor", lightColors[i]);
                RenderCube(cubeVAO);
            }


            

            glBindFramebuffer(GL_FRAMEBUFFER, 0);


            bool horizontal = true, first_iteration = true;
            unsigned int amount = 10;
            shaderBlur.Use();
            for (unsigned int i = 0; i < amount; i++)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
                shaderBlur.SetUniform1i("horizontal", horizontal);
                glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
                RenderQuad(quadVAO);
                horizontal = !horizontal;
                if (first_iteration)
                    first_iteration = false;
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
            // --------------------------------------------------------------------------------------------------------------------------
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            TestShader.Use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
            TestShader.SetUniform1i("bloom", bloom);
            TestShader.SetUniform1f("exposure", exposure);
            RenderQuad(quadVAO);

            std::cout << "bloom: " << (bloom ? "on" : "off") << "| exposure: " << exposure << std::endl;



            Key_Back(window);
            Find();



            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}


