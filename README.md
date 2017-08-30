# airmapd

## Development Workflow

`airmapd` uses CMake for building and testing. We envision the following development workflow:
```
# Clone airmapd and all its dependencies
git clone --recursive github.com/airmap/airmapd
# Please execute these commands at the root of the source tree
mkdir build
cd build && cmake .. && make
# Do some changes, iterate, be happy, get ready to issue a PR
make format
```

## Setup & Dependencies:

Please refer to the platform-specific `setup*.sh` scripts in the `tools/${PLATFORM}` subfolder. For Ubuntu, and under the assumption of `docker` being available,
you can bootstrap a development environment in a `docker` container with:
```
docker run -v $(PWD):/airmapd -it ubuntu:17.04 bash
tools/ubuntu/setup.dev.sh
```

## Running `airmapd` on Intel Aero

Please refer to https://airmap.atlassian.net/wiki/spaces/AIRMAP/pages/69992501/Intel+Aero for Intel Aero setup instructions.

Please note that these instructions only apply to Intel Aero images featuring `systemd`.
This is the case if you are using the latest Intel Aero image (1.5.1 at the time of this writing).

We rely on `docker` to deliver `airmapd` to the Intel Aero. For that, you first need to buid a docker container with the
following command line:
```
tools/build-docker-image.sh
```
Once the command finishes, you should save the container to a tarball by running:
```
docker save -o airmapd.tar.gz airmapd:latest
```
Copy the resulting `airmapd.tar.gz` to a USB stick, and mount the stick on the Intel Aero.
Restore the image on the Intel Aero by running:
```
docker load -i airmapd.tar.gz
```
Once the image is loaded, create the file `/lib/systemd/system/airmapd.service` with the following contents:
```
[Unit]
Description=The AirMap on-vehicle service

[Service]
EnvironmentFile=/etc/airmapd.env
ExecStart=/usr/bin/docker run airmapd:latest \
  --api-key=${AIRMAPD_API_KEY}\
  --user-id=${AIRMAPD_USER_ID}\
  --aircraft-id=${AIRMAPD_AIRCRAFT_ID}\
  --telemetry-host=api.k8s.stage.airmap.com\
  --telemetry-port=32003\
  --tcp-endpoint-ip=172.17.0.1\
  --tcp-endpoint-port=5760

[Install]
WantedBy=multi-user.target
```
Create the file `/etc/airmapd.env` with the following contents:
```
AIRMAPD_API_KEY=YOUR_API_KEY
AIRMAPD_USER_ID=YOUR_USER_ID
AIRMAPD_AIRCRAFT_ID=YOUR_AIRCRAFT_ID
```
Run `systemctl daemon-reload && systemctl enable airmapd` and reboot the vehicle. Check the output of the service with:
```
journalctl -f -u airmapd
```

### Missing `/etc/resolv.conf`

Depending on your setup and signal coverage, the `airmapd` service might start before `NetworkManager` succeeds in creating
a connection via the LTE modem. In this case, `/etc/resolv.conf` is missing and you might run into a known [docker issue](https://github.com/docker/libnetwork/pull/1847). Please wait for the LTE connection to be established and run `systemctl restart airmapd`.
