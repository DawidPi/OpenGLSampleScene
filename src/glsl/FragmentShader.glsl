#version 400

in vec2 fs_texCoords;
in vec4 normalPosition;
in vec4 worldPosition;
in float vertexDistanceFromLight;

uniform bool useLighting;
uniform bool isLightSource;
uniform vec4 cameraPosition;
uniform vec4 lookDirection;
uniform vec4 lightPosition;
uniform vec3 lightColor;
uniform sampler2D fs_texture;

out vec4 fs_color;


void main(void)
{
    vec4 chosenColor;
    chosenColor = texture(fs_texture, fs_texCoords);


    float colorAmbientScale = 0.001;
    vec3 ambientColor = vec3(colorAmbientScale, colorAmbientScale, colorAmbientScale) * chosenColor.rgb;

    if(isLightSource){
        float lightingFactor = dot(normalize(cameraPosition - worldPosition), normalize(normalPosition));
        fs_color = vec4(chosenColor.rgb, lightingFactor);
    } else {
        vec4 incidentRayDiffuseVector = vec4(lightPosition.xyz,0.0);
        float lightingFactor = dot(normalize(incidentRayDiffuseVector), normalize(normalPosition));
        lightingFactor = clamp(lightingFactor, 0.0, 1.0);

        vec4 incidentRayVector = normalize(lightPosition - worldPosition);
        vec3 eyeDirection = normalize(lookDirection.xyz);
        vec3 reflection = reflect(incidentRayVector.xyz, normalize(normalPosition.xyz));
        float reflectFactor = dot(eyeDirection, reflection);
        reflectFactor = max(0.0, reflectFactor);

        float lightPower = 8000;
        vec3 commonColor = chosenColor.rgb * lightColor /pow(vertexDistanceFromLight, 2);
        vec3 diffuseColor = commonColor * lightingFactor * lightPower;
        vec3 specularColor = vec3(0);// commonColor * pow(reflectFactor,50) * 25*lightPower/(distance(cameraPosition, worldPosition));
        fs_color = vec4(ambientColor + diffuseColor + specularColor, chosenColor.a);
    }
}