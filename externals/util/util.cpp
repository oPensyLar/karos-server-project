#include "util.h"

int util::block_despues_rand(int val_rand)
{
    // Como que siempre da el mismo valor que val_rand
    auto d = idiv(val_rand, 0x1F31D);

    d['q'] = d['q'] * 0x0B14;
    d['r'] = d['r'] * 0x41A7;

    return d['r'] - d['q'];
}

int util::print_vector(std::vector<int> arg0)
{
    for (int i = 0x0; i < arg0.size(); i++)
    {
        std::cout << "0x" << std::hex << arg0.at(i) << ", ";
    }

    std::cout << std::endl;

    return 0;
}

int util::get_data_len(std::vector<uint8_t> data)
{

    auto vec_len = data;
    vec_len.resize(0x4);
    std::stringstream sstream;
    int ret;

    for (auto it = vec_len.begin(); it < vec_len.end(); it++)
        sstream << std::hex << (int)*it;

    sstream >> ret;

    return ret;
}  


std::map<char, int> util::idiv(int num, int denom)
{

    div_t div_result = std::div(num, denom);

    std::map<char, int> ret;

    ret['r'] = div_result.rem;
    ret['q'] = div_result.quot;

    return ret;
}


int util::gen_random(int max)
{
    return 0;
}


void util::sleep(int milis)
{
}

bool util::load_bin(const std::string& file_path, std::vector<uint8_t>* out_buffer)
{
    std::ifstream file_ifstream(file_path, std::ios::binary);

    if (!file_ifstream)
        return false;

    out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
    file_ifstream.close();

    return true;
}
