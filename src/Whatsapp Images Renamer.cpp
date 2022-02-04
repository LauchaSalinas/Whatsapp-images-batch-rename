#include <iostream>
#include <string>
#include <filesystem>  //std::filesystem::path, std::filesystem::recursive_directory_iterator

std::string changeFileName(const std::string& currentFileName, const std::string& extension)
{
    std::cout << "Nombre previo a la modificación: " << currentFileName << "\n";

    // ....other logics regarding current filename

    const std::string newFileName{ currentFileName + " (0)" + extension};
    std::cout << "Nombre luego de la modificación: " << newFileName << "\n";
    return newFileName; // new file name
}

int main()
{

    std::string strpath;
    std::cout << "Ingrese la ruta completa de la carpeta con imagenes de Whatsapp a renombrar: "<< std::endl;
    std::cout << "C:\\Users\\user\\Downloads\\WhatsApp Unknown YEAR - MM - DD at HH.MM.SS HT" << std::endl;
    
    std::getline(std::cin, strpath);

    const std::filesystem::path myPath = strpath;
    const std::string extension{ ".jpeg" };
 
    // iterate through all the files in the directory
    for (const auto& dirEntry : std::filesystem::directory_iterator(myPath))
    {
        // checks if the file's extension and name is up to be changed

        if (std::filesystem::is_regular_file(dirEntry) && dirEntry.path().extension() == extension && std::string::npos == dirEntry.path().stem().string().find(')'))
        {
            const std::string currentFileName{ dirEntry.path().filename().string() };
            const std::string currentFileNameWE{ dirEntry.path().stem().string() }; // same as before but without extension
            // following function is meant for the logic to provide the new file names in the directory
            const std::string newFileName{ changeFileName(currentFileNameWE, extension) };
            try
            {
                std::filesystem::rename(myPath / currentFileName, myPath / newFileName);
            }
            catch (std::filesystem::filesystem_error const& error)  // catch the errors(if any)!
            {
                std::cout << error.code() << "\n" << error.what() << "\n";
            }
        }

    }

    std::cout << std::endl << std::endl << "Presione una tecla para finalizar";
    std::cin.get();
}