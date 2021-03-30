if ! [ -d ../../../shaders ]; then
mkdir ../../../shaders
fi

/bin/glslc  shader.vert -o ../../../shaders/vert.spv
/bin/glslc  shader.frag -o ../../../shaders/frag.spv