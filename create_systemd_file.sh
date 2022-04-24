#/bin/bash

tee /etc/systemd/system/postgresparser.service <<EOF
 [Unit]
 Description=Watches postgres csv logs and sends it to designated Graylog server

 [Service]
 User=root
 ExecStart=/home/berkay/projects/postgres-csv-log-parser/cmake-build-debug/postgres_csv_parser
 Restart=on-failure

 [Install]
 WantedBy=multi-user.target
EOF