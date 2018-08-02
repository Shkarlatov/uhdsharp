/*******************************************************************************

Copyright(c) 2014 Nir Eden, 4Z7DEF  https://uhdsharp.codeplex.com/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#pragma once
#pragma managed

#include <iostream>
#include <string>
//using namespace Ionic::Zip;

namespace UHD_SHARP {

	private ref class CheakFilesTree
	{

	private:

		// Source: http://www.digitalcoding.com/Code-Snippets/CPP-CLI/C-CLI-Code-Snippet-Download-File-from-URL.html
		void downloadFile(System::String ^_URL, System::String ^_saveAs)
		{
			try
			{
				System::Net::WebClient ^webClient = gcnew System::Net::WebClient();
				// Downloads the resource with the specified URI to a local file.
				webClient->DownloadFile(_URL, _saveAs);
				//webClient->Dispose();//->Dispose();
			}
			catch (System::Exception ^_e)
			{
				// Error
				System::Console::WriteLine("Exception caught in process: {0}", _e);
			}
		}

		void extractFromAssembly(String^ name)
		{
			// Source: http://stackoverflow.com/questions/7259286/how-can-i-include-a-zip-file-in-a-net-c-cli-assembly
			Reflection::Assembly^ a1 = Reflection::Assembly::GetExecutingAssembly();

			//cli::array<String^>^ names = a1->GetManifestResourceNames();
			//for each(String^ name in names)
			//{
				IO::BinaryReader^ s1 = gcnew IO::BinaryReader(a1->GetManifestResourceStream(name));

				String^ fileName = name;
				IO::BinaryWriter^ sw = gcnew IO::BinaryWriter(IO::File::Open(fileName, IO::FileMode::Create));
				sw->Write(s1->ReadBytes(s1->BaseStream->Length));
				sw->Flush();
				sw->Close();
			//}

		}

	public:
		CheakFilesTree()
		{
			//if (not System::IO::File::Exists("uhd.dll"))
			//{
			//	std::cout << "No uhd.dll found. Extracting..." << std::endl;
			//	extractFromAssembly("uhd.dll");
			//}
			//	std::cout << "No uhd.dll found. Downloading from repo..." << std::endl;
			//	downloadFile("https://github.com/4z7def/UHD-CSHARP/raw/master/bin/uhd.dll", "uhd.dll");
			//}
			//String^ ImagesFolder = Environment::GetEnvironmentVariable("UHD_CSHARP_IMAGES_FOLDER");
			//if (ImagesFolder == nullptr) // EnvironmentVariable not found
			//{
			//	Console::WriteLine("!-- Images folder was not found");
			//	try
			//	{
			//		// Downloading
			//		ImagesFolder = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData) + "\\UHD_CSHARP_IMAGES";
			//		String^ ImagesZipFile = ImagesFolder + "\\images.zip";
			//		System::IO::Directory::CreateDirectory(ImagesFolder);
			//		Console::WriteLine("!-- Downloading images from Ettus web site. This may take a while...");
			//		downloadFile("http://files.ettus.com/binaries/images/uhd-images_003.008.000-release.zip", ImagesZipFile);
			//		// Extract zip file
			//		extractFromAssembly("Ionic.Zip.dll");
			//		ZipFile^ zip = ZipFile::Read(ImagesZipFile);
			//		zip->ExtractAll(ImagesFolder, ExtractExistingFileAction::OverwriteSilently);
			//		// Delete zip file
			//		System::IO::File::Delete(ImagesZipFile);
			//		// Set environment variable
			//		Environment::SetEnvironmentVariable("UHD_CSHARP_IMAGES_FOLDER", ImagesFolder);
			//	}
			//	catch (Exception^ ex1)
			//	{
			//		Console::WriteLine("exception: " + ex1);
			//	}


			//	//cli::array<String^>^ files = System::IO::Directory::GetFiles(ImagesFolder + "\\uhd-images_003.008.000-release.zip");
			//	//std::array<int, 2> RXDataLength; // Double buffer for RX data length
			//}
			//Console::WriteLine("Images path " + ImagesFolder);


			////if (not System::IO::Directory::Exists("images"))
			////{
			////	System::IO::File::Copy(".\zlib.zip\*.*", ".");
			////	std::cout << "No images found. Extracting..." << std::endl;
			////	//CreateObject("Shell.Application");
			//////	downloadFile("http://files.ettus.com/binaries/images/uhd-images_003.008.000-release.zip", "uhd-images_003.008.000-release.zip");
			//////	System::IO::Compression::GZipStream::Write()
			////}


		}

		~CheakFilesTree()
		{
		}

	};

}