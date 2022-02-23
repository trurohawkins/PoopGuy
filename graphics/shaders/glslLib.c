#ifndef GLSLLIB
#define GLSLLIB
const char* matVS = "#version 330\nuniform mat4 tMat;\nuniform mat4 sMat;\nuniform mat4 rMat;\nin vec2 vp;\nvoid main() {	\ngl_Position = tMat * rMat * sMat * vec4(vp.x, vp.y, 0.0, 1.0);\n}\n";
const char* matFS = "#version 330\nuniform vec4 inputColor;\nout vec4 fragColor;\nvoid main() {\nfragColor = inputColor;\n}\n";
const char* texVS = "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec4 aColor;\nlayout (location = 2) in vec2 aTexCoord;\nlayout (location = 3) in vec4 aOffset;\nlayout (location = 4) in vec4 rotations;\nlayout (location = 5) in vec2 texOffset;\n\nout vec4 ourColor;\nout vec2 TexCoord;\n\nuniform mat4 tMat;\nuniform mat4 rMat;\nuniform mat4 sMat;\nuniform mat3 tcScale;\nuniform mat3 tcTrans;\nuniform vec2 texCoordShift;\n\nvoid main()\n{\nif(aOffset.z == 1) {\nmat4 tm = tMat;\ntm[3][0] = aOffset.x;\ntm[3][1] = aOffset.y;\nmat4 rm = rMat;\nrm[0][0] = rotations.x;\nrm[1][0] = rotations.y;\nrm[0][1] = rotations.z;\nrm[1][1] = rotations.w;\ngl_Position = tm * rm * sMat * vec4(aPos, 1.0);\nmat3 tc = tcTrans;\ntc[2][0] = texOffset.x;\ntc[2][1] = texOffset.y;\nvec3 Tex =  tc * tcScale * vec3(aTexCoord, 1.0);\nTexCoord = vec2(Tex.x, Tex.y);\nourColor = aColor;\n}\n}\n";
const char* texFS = "#version 330 core\nout vec4 FragColor;\n\nin vec4 ourColor;\nin vec2 TexCoord;\n\nuniform vec4 colorShift;\nuniform sampler2D ourTexture;\nuniform vec2 TexCoordShift;\n\nvoid main()\n{\nvec4 texColor = texture(ourTexture, TexCoord);\nFragColor = vec4(texColor.x * colorShift.x * ourColor.x, texColor.y * colorShift.y * ourColor.y, texColor.z * colorShift.z * ourColor.z, texColor.w * colorShift.w * ourColor.w);\n}\n";
const char* singleTexVS = "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 aColor;\nlayout (location = 2) in vec2 aTexCoord;\n\nout vec3 ourColor;\nout vec2 TexCoord;\n\nuniform mat4 tMat;\nuniform mat4 rMat;\nuniform mat4 sMat;\nuniform mat3 tcScale;\nuniform mat3 tcTrans;\nuniform vec2 texCoordShift;\n\n\nvoid main()\n{\ngl_Position = tMat * rMat * sMat * vec4(aPos, 1.0);\nourColor = aColor;\nvec3 Tex =  tcTrans * tcScale * vec3(aTexCoord, 1.0);\nTexCoord = vec2(Tex.x, Tex.y);\n}\n";
const char* singleTexFS = "#version 330 core\nout vec4 FragColor;\n\nin vec3 ourColor;\nin vec2 TexCoord;\n\nuniform vec4 colorShift;\nuniform sampler2D ourTexture;\nuniform vec2 TexCoordShift;\n\nvoid main()\n{\nvec4 texColor = texture(ourTexture, TexCoord);\nFragColor = vec4(texColor.x * colorShift.x, texColor.y * colorShift.y, texColor.z * colorShift.z, texColor.w * colorShift.w);\n}\n";
#endif
