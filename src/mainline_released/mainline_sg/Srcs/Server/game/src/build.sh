echo "### Metin2 Game Builder ###"
echo "### Cleaning ...."
gmake clean
echo "### Building ###"
gmake -j20 > ../GAME_BUILD_LOG.txt 2> ../GAME_ERROR_LOG.txt
echo "### Done Building ###"