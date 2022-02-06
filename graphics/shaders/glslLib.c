#ifndef GLSLLIB
#define GLSLLIB
const char* matFS = "#version 330\nuniform vec4 inputColor;\nout vec4 fragColor;\nvoid main() {\nfragColor = inputColor;\n}\n";
const char* matVS = "#version 330\nuniform mat4 tMat;\nuniform mat4 sMat;\nuniform mat4 rMat;\nin vec2 vp;\nvoid main() {	\ngl_Position = tMat * rMat * sMat * vec4(vp.x, vp.y, 0.0, 1.0);\n}\n";
const char* texFS = "#version 330 core\nout vec4 FragColor;\n\nin vec3 ourColor;\nin vec2 TexCoord;\n\nuniform vec3 colorShift;\nuniform sampler2D ourTexture;\nuniform vec2 TexCoordShift;\n\nvoid main()\n{\nvec4 texColor = texture(ourTexture, TexCoord);\nFragColor = vec4(texColor.x * colorShift.x, texColor.y * colorShift.y, texColor.z * colorShift.z, texColor.w);\n}\n";
const char* texVS = "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 aColor;\nlayout (location = 2) in vec2 aTexCoord;\n\nout vec3 ourColor;\nout vec2 TexCoord;\n\nuniform mat4 tMat;\nuniform mat4 rMat;\nuniform mat4 sMat;\nuniform mat3 tcScale;\nuniform mat3 tcTrans;\nuniform vec2 texCoordShift;\n\nvoid main()\n{\ngl_Position = tMat * rMat * sMat * vec4(aPos, 1.0);\nourColor = aColor;\nvec3 Tex =  tcTrans * tcScale * vec3(aTexCoord, 1.0);\nTexCoord = vec2(Tex.x, Tex.y);\n}\n";
#endif
