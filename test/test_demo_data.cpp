#include <vector>

#include "content_generator.h"
#include "demo_data.h"
#include "test_framework.h"
/* build task settings configuration:
"args":[
        "-g",
        "/home/y24/NDSL/test/test_demo_data.cpp",
        "-I",
        "/home/y24/NDSL/include",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}",
        "/home/y24/NDSL/src/content_generator.cpp",
        "/home/y24/NDSL/src/demo_data.cpp",
        ], */
std::vector<DemoData> generateDemoDataset() {
  DataFactory factory;
  ContentGenerator contentGenerator;
  std::vector<DemoData> res;
  res.emplace_back(data_invalid);
  res.emplace_back(session_init, contentGenerator.generate(12));
  res.emplace_back(session_pair, factory.toString(time(nullptr)),
                   contentGenerator.generate(12));
  res.emplace_back();
  res.emplace_back(res[2]);
  return res;
}
void test(DemoData& data) {
  std::string str = data.toStr();
  DemoData newData = DemoData(str);
  DemoTest::assertEqual(data.getHeader().timestamp,
                        newData.getHeader().timestamp);
  DemoTest::assertEqual(data.getHeader().type, newData.getHeader().type);
  DemoTest::assertEqual(data.getBody().content, newData.getBody().content);
}

int main(int argc, char const* argv[]) {
  auto demoDataset = generateDemoDataset();
  for (auto data : demoDataset) test(data);
  return 0;
}
