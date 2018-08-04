# Configuration begin.
template_prefix=sbadmin2_page_
template=template_01
# Configuration end.
template=${template_prefix}${template}
template_dash=$(echo $template | sed 's/_/-/g')

echo This script will clone page based on \"${template}\" module.
read -p "Module machine name:"  -i $template_prefix -e newmodule
if [[ $newmodule =~ [^a-z_0-9] ]];then
    echo Machine name harus huruf kecil, underscore, dan angka.
fi
if [[ $newmodule =~ ^[0-9] ]];then
    echo Machine name tidak boleh diawali oleh angka.
fi
newmodule_dash=$(echo $newmodule | sed 's/_/-/g')





echo Copy template
cp -rf $template $newmodule

echo Change directory to $newmodule
cd $newmodule

echo Rename file
find . -name "*${template}*" | while IFS= read -r f; do\
   mv -v "$f" "$(echo "$f" | sed -e 's/'${template}'/'${newmodule}'/' - )"; \
done

echo Rename file dash.
find . -name "*${template_dash}*" | while IFS= read -r f; do\
   mv -v "$f" "$(echo "$f" | sed -e 's/'${template_dash}'/'${newmodule_dash}'/' - )"; \
done

echo Rename content
find . -type f -print0 | xargs -0 sed -i 's/'${template}'/'${newmodule}'/g'

echo Rename content
find . -type f -print0 | xargs -0 sed -i 's/'${template_dash}'/'${newmodule_dash}'/g'

echo Edit file .info
sed -i '/hidden = TRUE/d' ./${newmodule}.info

template_path=$(echo $template | sed 's/'${template_prefix}'//')
newmodule_path=$(echo $newmodule | sed 's/'${template_prefix}'//')

echo 'Edit informasi path pada hook_menu().'
sed -i "s/'${template_path}'/'${newmodule_path}'/g" ./${newmodule}.module


template_title=$(echo $template_path | sed -r --expression 's/(^|-)(\w)/\U\2/g' --expression 's/_/ /g')
newmodule_title=$(echo $newmodule_path | sed -r --expression 's/(^|-)(\w)/\U\2/g' --expression 's/_/ /g')


echo 'Edit informasi title pada hook_menu().'
sed -i "s/'${template_title}'/'${newmodule_title}'/g" ./${newmodule}.module



