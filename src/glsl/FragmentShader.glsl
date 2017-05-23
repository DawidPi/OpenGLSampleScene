#version 400

in vec4 fragmentColor;
in vec2 fs_texCoords;
in vec4 normalPosition;
in vec4 worldPosition;
in float vertexDistanceFromLight;

uniform bool useTexture;
uniform bool useLighting;
uniform bool isLightSource;
uniform vec4 cameraPosition;
uniform vec4 lookDirection;
uniform vec4 lightPosition;
uniform sampler2D fs_texture;

out vec4 fs_color;

void main(void)
{
    vec4 chosenColor;

    if(useTexture)
        chosenColor = texture(fs_texture, fs_texCoords);
    else{
        chosenColor = fragmentColor;
    }

    float colorAmbientScale = 0.2;
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

        vec3 lightColor = vec3(1.0, 1.0, 1.0);
        float lightPower = 30000;
        vec3 commonColor = chosenColor.rgb * lightColor /pow(vertexDistanceFromLight,2);
        vec3 diffuseColor = commonColor * lightingFactor * lightPower;
        vec3 specularColor = commonColor * pow(reflectFactor, 199) * lightPower*0.3/(0.75*distance(cameraPosition, worldPosition));
        fs_color = vec4(ambientColor + diffuseColor + specularColor, chosenColor.a);
    }
}