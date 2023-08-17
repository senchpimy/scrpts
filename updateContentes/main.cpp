#include <iostream>
#include <iterator>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
#include <pwd.h>
#include <sys/stat.h>
#include <filesystem>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

namespace fs = std::filesystem;

using namespace std;


int main(int argc, char *argv[])
{
  struct passwd *pw = getpwuid(getuid());
  string homedir = pw->pw_dir;
  int homedir_int = homedir.size();
  string main_dir = homedir + "/AI/";
  string models_dir = main_dir + "models/";

  /* Name of the directory in the main directory*/
  string models_dirs[]={
  "checkpoints",
 "clip",
 "clip_vision",
 "controlnet",
 "diffusers",
 "embeddings",
 "gligen",
 "hypernetworks",
 "loras",
 "mmdets",
 "onnx",
 "sams",
 "style_models",
 "ultralytics",
 "unet",
 "upscale_models",
 "vae",
 "vae_approx",
 "lycoris",
  //"adetailer"
  };

  /* Name of the directory in the system directory*/
  string locations[] = {"ComfyUI/models/", "stable-diffusion-webui/"};
  int total_locations = 2;

  /* Name of the directory in the system directory*/
  
  string total[][total_locations] = {
    {"checkpoints","models/Stable-diffusion"},
    {"clip"},
    {"clip_vision"},
    {"controlnet","models/ControlNet"},
    {"diffusers"},
    {"embeddings", "embeddings"},
    {"gligens"},
    {"hypernetworks", "models/hypernetworks"},
    {"loras", "models/Lora"},
    {"mmdets"},
    {"onnx"},
    {"sams"},
    {"style_models"},
    {"ultralytics"},
    {"unet"},
    {"upscale_models", "models/RealESRGAN"},
    {"vae", "models/VAE"},
    {"vae_approx", "models/VAE-approx"},
    {"", "models/LyCORIS"},
    // adetailer
  };
  int total_categories = 19;
  struct stat sb;

  for (int i = 0; i<total_categories ; i++) {
    for (int j = 0; j<total_locations; j++){
      if (total[i][j].size()>0){
        string path = main_dir+locations[j]+total[i][j];
        if (!fs::is_directory(path)){
          mkdir(path.c_str(), 0755);
          cout<<"Directory "+path+"created\n";
        }
        string path_to_read = models_dir+models_dirs[i];
        for (const auto & entry : fs::directory_iterator(path_to_read)){
          string target_location = path + "/" + (string) entry.path().filename();
          if(!fs::exists(target_location)){
            fs::create_symlink(entry.path(), target_location);
            cout<<"Created symlink in "<<target_location<<"\n";
          } 
        }
      }
    }
  }

  return EXIT_SUCCESS;
}
