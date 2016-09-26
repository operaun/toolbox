#!/bin/sh

MY_IP=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
DISTCC_DIR=${BASEDIR}/distcc
HOSTS_DIR=/usr/local/etc/distcc

sudo pkg install -y distcc

sudo mkdir ${HOSTS_DIR}
sudo ln -s ${DISTCC_DIR}/distcc_hosts.conf ${HOSTS_DIR}/hosts

#grep ${MY_IP}/24 ${DISTCC_DIR}/distcc_hosts.conf || echo ${MY_IP}/24 >> ${DISTCC_DIR}/distcc_hosts.conf

grep distccd_enable /etc/rc.conf || echo "distccd_enable=\"YES\"" | sudo tee -a /etc/rc.conf > /dev/null
grep distccd_flags /etc/rc.conf || echo "distccd_flags=\"--allow 192.168.11.0/24 --listen ${MY_IP} --port 3632 --user distcc --log-file=/var/log/distccd.log --daemon -P /var/run/distccd.pid -N 20 -j 5\"" | sudo tee -a /etc/rc.conf > /dev/null

grep ${HOME}/.profile CCACHE_PREFIX || echo "export CCACHE_PREFIX=\"distcc\"" | tee -a ${HOME}/.profile > /dev/null

sudo touch /var/log/distccd.log
sudo chown distcc:daemon /var/log/distccd.log

sudo service distccd start

#echo "distcc_hosts.conf 파일은 devel에 push 해주세요."
echo "다시 로그인 하시면 distcc가 적용됩니다."
