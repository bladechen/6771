#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class File {
public:
  File(const std::string& contents): contents{contents} {}

  virtual std::unique_ptr<File> clone() const = 0;
  virtual const std::string& read() const { return contents; }
  virtual ~File() = default;

protected:
  // contents really shouldn't be defined here, but for the sake of conciseness
  std::string contents;
};

class ExtF: public File {
public:
  ExtF(const std::string& contents): File{contents} {}

  std::unique_ptr<File> clone() const override {
    return std::make_unique<ExtF>(*this);
  }
};

class NF: public File {
public:
  NF(const std::string& contents): File{contents} {}

  std::unique_ptr<File> clone() const override {
    return std::make_unique<NF>(*this);
  }
};

// TODO: what makes this example convoluted or unrealistic?
// Why do we have to make it so in order to show covariant return types
// (ie. what would stop us from using covariant return types)
// TODO: try non-reference types
class FileSystem {
public:
  virtual File& open(const std::string& path) = 0;
  virtual void close(File&) {}
  virtual ~FileSystem() = default;
};

// note: these two classes have exactly the same content, modulo naming
// in reality, they would have different implementations
class ExtFS: public FileSystem {
public:
  ExtFS(const std::map<std::string, ExtF>& files): files{files} {}
  ExtF& open(const std::string& path) override {
    return files.at(path);
  }

private:
  std::map<std::string, ExtF> files;
};

class NFS: public FileSystem {
public:
  NFS(const std::map<std::string, NF>& files): files{files} {}

  NF& open(const std::string& path) override {
    return files.at(path);
  }

private:
  std::map<std::string, NF> files;
};

int main() {
  ExtFS extfs_con{{{"extfs_filename", ExtF{"ext contents"}}}};
  NFS nfs_con{{{"nfs_filename", NF{"nfs contents"}}}};

  FileSystem& extfs = extfs_con;
  FileSystem& nfs = nfs_con;

  std::vector<File*> files;
  files.push_back(&extfs.open("extfs_filename"));
  files.push_back(&nfs.open("nfs_filename"));
  for (const auto& file : files)
    std::cout << file->read() << '\n';
}

