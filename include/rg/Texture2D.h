//
// Created by matf-rg on 30.10.20..
//
//

#ifndef PROJECT_BASE_TEXTURE2D_H
#define PROJECT_BASE_TEXTURE2D_H
// mi17505 17.04.22.
#include <glad/glad.h>
#include <stb_image.h>
#include <rg/Error.h>

class Texture2D{
    unsigned int m_Id;

public:
    Texture2D(std:: string pathToImg,GLenum filtering=GL_REPEAT,GLenum sampling=GL_LINEAR,bool rgbA=false){
        unsigned int tex0;
        glGenTextures(1,&tex0); //generisemo tekstura objekat

        glBindTexture(GL_TEXTURE_2D,tex0);

        //wrap
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,sampling);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,sampling);

        //filter
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filtering);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filtering);


        //looad img
        int width,height,nChannel;
        stbi_set_flip_vertically_on_load(true);

        ASSERT(!pathToImg.empty(), "Check path to img!! --> "<<pathToImg << "<----\n");
        unsigned char* data =stbi_load(pathToImg.c_str(),&width,&height,&nChannel,0);

        //argument rgbA sluzi da znamo da li je u pitanju png ili jpg da
        if(data){
            if(!rgbA) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else{
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }

        }
        else{

            std::cerr<< "Failed to load img";
        }
        stbi_image_free(data);

        m_Id=tex0;

    }



    void active(GLenum e){
        glActiveTexture(e);
    }
    void bind(){
        glBindTexture(GL_TEXTURE_2D,m_Id);
    }



};


#endif //PROJECT_BASE_TEXTURE2D_H
