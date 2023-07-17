#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

// Sampler de textura
uniform sampler2D textura;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    vec3 texColor = texture2D(textura, TexCoord).rgb;

    // Luz ambiente
    float intensidadeAmbiente = 0.35;
    vec3 luzAmbiente = intensidadeAmbiente * lightColor;
  	
    // Luz difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 luzDifusa = diff * lightColor;
    
    // Luz especular
    float intensidadeEspecular = 2.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 luzEspecular = intensidadeEspecular * spec * lightColor;

    // Luz Phong (combinação das 3)
    // Multiplica por objectColor se eu quiser iluminação nas cores.
    // Multiplica por texColor se eu quiser iluminação na textura.
    vec3 result = (luzAmbiente + luzDifusa + luzEspecular) * texColor;
    FragColor = vec4(result, 1.0);
} 