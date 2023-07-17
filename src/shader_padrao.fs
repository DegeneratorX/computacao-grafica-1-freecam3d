#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

// Sampler de textura
uniform sampler2D texAsfalto;
uniform sampler2D texCalcada;
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    vec3 texColorAsfalto = texture2D(texAsfalto, TexCoord).rgb;
    vec3 texColorCalcada = texture2D(texCalcada, TexCoord).rgb;

    // Luz ambiente
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Luz difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Luz especular
    float specularStrength = 2.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Luz Phong (combinação das 3)
    // Multiplica por objectColor se eu quiser iluminação nas cores.
    // Multiplica por texColor se eu quiser iluminação na textura.
    vec3 result = (ambient + diffuse + specular) * texColorAsfalto;
    FragColor = vec4(result, 1.0);
} 